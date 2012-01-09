/*
 * Copyright (C) 2010 Fabian Gammenthaler, Michael Kohler
 *
 * BackupSoft is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Contributors:
 *   none
 *
 */

#include <QtGui>
#include "helper.h"
#include "alertwindow.h"

/*
 * Constructor
 */
Helper::Helper()
{
}

/*
 * writes to a file.
 *
 * @params:
 *     - aFileName : file name
 *     - aAppend : should the text be appended or overwritten?
 *     - aData : data that needs to be written
 * @return: none
 */
void Helper::writeFile(QString aFileName, bool aAppend, QByteArray aData)
{
  QFile file(aFileName);
  bool success;
  if (aAppend)
    success = file.open(QIODevice::WriteOnly | QIODevice::Append);
  else
    success = file.open(QIODevice::WriteOnly);

  if (success) {
    file.write(aData);
    file.close();
  }
  else {
    QString errorMsg = "Could not open ";
    errorMsg.append(aFileName);
    errorMsg.append(".. Please make sure it is existent and readable.");
    AlertWindow *alertWin = new AlertWindow("ERROR", "", errorMsg);
    alertWin->show();
  }
}

/*
 * overwrites a current profile
 *
 * @params:
 *     - aFileName : file name
       - aProfile : old profile
 *     - aAppend : should the text be appended or overwritten?
 *     - aData : data that needs to be written
 * @return: none
 */
void Helper::overwriteFile(QString aFileName, QString aProfile, bool aAppend, QString aData)
{
  QStringList *fileData;
  QString data, temp;
  QFile file(aFileName);
  int index;
  bool success;
  fileData = readFile(aFileName);
  for(int i = 0; i < fileData->length(); i++) {
    temp = fileData->value(i);
    if(temp == aProfile) {
      index = i;
      break;
    }
  }
  file.open(QIODevice::WriteOnly);
  success = file.remove();
  if(success) {
    fileData->replace(index, aData);
    for(int i = 0; i < fileData->length(); i++) {
      data = fileData->value(i);
      if(i != 0)
        data.append("\n");
      writeFile(aFileName, aAppend, data.toLatin1());
    }
    file.close();
  }
  else {
    QString errorMsg = "Error by overwriting the file";
    AlertWindow *alertWin = new AlertWindow("ERROR", "", errorMsg);
    alertWin->show();
  }
}

/*
 * reads from a file.
 *
 * @params:
 *     - aFileName : file name
 *
 *  @return:
 *     - QByteArrayList data : the read data
 */
QStringList* Helper::readFile(QString aFileName)
{
  // read the data line by line
  QFile *file = new QFile(aFileName);
  QStringList *data = new QStringList();
  if (file->open(QIODevice::ReadOnly) ) {
    // file opened successfully
    QTextStream *tstream = new QTextStream(file);
    while (!tstream->atEnd()) {
      data->append(tstream->readLine());
    }
    file->close();
  }
  else {
    QString errorMsg = "Could not open " + aFileName + ".. Please make sure it is existent and readable.";
    AlertWindow *alertWin = new AlertWindow("ERROR", "", errorMsg);
    alertWin->show();
  }

  return data;
}

/*
 * deletes the selected profile.
 *
 * @params:
 *     - aFileName : file name
       - aProfile : profile name
 * @return: none
 */
void Helper::deleteProfile(QString aFileName, QString aProfile)
{
  QStringList *fileData;
  QString data, temp;
  QFile file(aFileName);
  int index;
  bool success;
  bool aAppend = true;
  fileData = readFile(aFileName);
  for(int i = 0; i < fileData->length(); i++) {
    temp = fileData->value(i);
    if(temp == aProfile) {
      index = i;
      break;
    }
  }
  file.open(QIODevice::WriteOnly);
  success = file.remove();
  if(success) {
    fileData->removeAt(index);
    if (fileData->length() == 0) {
      writeFile(aFileName, aAppend, data.toLatin1());
    }
    else {
      for(int i = 0; i < fileData->length(); i++) {
        data = fileData->value(i);
        data.append("\n");
        writeFile(aFileName, aAppend, data.toLatin1());
      }
    }
    file.close();
  }
  else {
    QString errorMsg = "Error while overwriting the file. Please try again.";
    AlertWindow *alertWin = new AlertWindow("ERROR", "", errorMsg);
    alertWin->show();
  }
}
