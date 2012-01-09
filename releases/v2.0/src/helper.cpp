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

#include <QDialog>
#include "helper.h"
#include "alertwindow.h"

Helper::Helper()
{
}



/*====================I/O====================*/

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
    QString msg = tr("Could not open %1.. Please make sure it is existent and readable.").arg(aFileName);
    AlertWindow *alertWin = new AlertWindow("ERROR", msg);
    alertWin->show();
  }
}

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
      data = fileData->value(i) + "\n";
      writeFile(aFileName, aAppend, data.toLatin1());
    }
    file.close();
  }
  else {
    QString msg = tr("An error occured while overwriting the configuration file. We are sorry for the inconvenience.");
    AlertWindow *alertWin = new AlertWindow("ERROR", msg);
    alertWin->show();
  }
}

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

    // ignore whitespaces
    for (int i = 0; i < data->length(); i++) {
      if (data->value(i) == "") {
        data->removeAt(i);
      }
    }
  }
  else {
    QString msg = tr("Could not open %1.. Please make sure it is existent and readable.").arg(aFileName);
    AlertWindow *alertWin = new AlertWindow("ERROR", msg);
    alertWin->show();
  }

  return data;
}



/*====================PROFILEMANAGEMENT====================*/

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
    QString msg = tr("Error while overwriting the file. Please try again.");
    AlertWindow *alertWin = new AlertWindow("ERROR", msg);
    alertWin->show();
  }
}



/*====================PROPERTIES====================*/

QStringList* Helper::readProperties()
{
  QStringList *lineList = readFile("settings.bs");
  QStringList *prefs = new QStringList[1];
  for (int i = 0; i < lineList->length(); i++) {
    QString tempString = lineList->at(i);
    QStringList extractedData = tempString.split('|', QString::SkipEmptyParts);
    prefs->append(extractedData[1]);
  }
  if (lineList->length() == 0) {
    for (int i = 0; i < 3; i++)
      prefs->append("");
  }
  return prefs;
}
