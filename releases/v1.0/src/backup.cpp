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
#include "backup.h"
#include "helper.h"

/*
 *
 * Constructor
 *
 */
Backup::Backup()
{
  initWindow();
}

/*
 * initializes the backup.
 *
 * @params: none
 * @return: none
 */
void Backup::initBackup()
{
  // get sources and destinations
  helper = new Helper();
  QStringList *profiles = helper->readFile("profile.bs");
  size = new QLabel(this);
  size->setGeometry(25, 20, 450, 20);
  size->show();

  // get filesize of the whole backup.
  filesize = 0;
  currentfilesize = 0;
  QString sourcePath = "";
  QString destPath = "";
  int a = 0;
  for (int i = 0; i < profiles->length(); i++) {
    QString temp = profiles->at(i);
    profileInformation.append(temp.split('|', QString::SkipEmptyParts));
    sourcePath = profileInformation.at(a+1);
    destPath = profileInformation.at(a+2);
    calcBackup(sourcePath, destPath, sourcePath);
    a = a + 3;
  }

  // do the backup.
  sourcePath = "";
  destPath = "";
  current = new QString("0");
  total = new QString("");
  total->setNum(filesize/1.0, 'g', 10);
  size->setText(*current + " MB of " + *total + " MB");
  a = 0;
  for (int i = 0; i < profiles->length(); i++) {
    sourcePath = profileInformation.at(a + 1);
    destPath = profileInformation.at(a + 2);
    runBackup(sourcePath, destPath, sourcePath);
    a = a + 3;
  }
  size->setText("Finished copying " + *total + " MB.. You can now close the window.");
  closeButton->setVisible(true);
  connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
}

/*
 * initializes the window.
 *
 * @params: none
 * @return: none
 */
void Backup::initWindow()
{
  setModal(true);
  resize(500, 150);
  setWindowIcon(QIcon("icons/backupsoft.png"));
  setWindowTitle("Backup running..");

  progress = new QProgressBar(this);
  progress->setGeometry(25, 50, 450, 20);
  progress->reset();

  closeButton = new QPushButton("Close", this);
  closeButton->setGeometry(200, 110, 100, 30);
  closeButton->setVisible(false);
}

/*
 * Calculates the size of the backup.
 *
 * @params:
 *  - QString aSourcePath: the source path to the folder that needs to be processed
 *  - QString aDestinationPath: the destination path
 *  - QString aOriginalPath: the path which the calculation started from
 * @return: none
 */
void Backup::calcBackup(QString aSourcePath, QString aDestinationPath, QString aOriginalPath)
{
  // Count all files and filesizes.
  QDir *directory = new QDir(aSourcePath);
  QStringList filesList = directory->entryList(QDir::NoFilter, QDir::DirsFirst);
  for (int i = 0; i < filesList.length(); i++) {
    QString temp = filesList.at(i);
    QString wholePath = aSourcePath + "/" + temp;
    QString tempDest = aDestinationPath + "/" + temp;
    // ignore '.' and '..' (filtering them automatically doesn't work)
    if (!temp.compare(".") || !temp.compare(".."))
      continue;

    if (isFolder(wholePath)) {
      calcBackup(wholePath, tempDest, aOriginalPath);
    }
    else {
      QStringList *lineList = helper->readFile("settings.bs");
      QString tempString = lineList->at(0);
      QStringList extractedData = tempString.split('|', QString::SkipEmptyParts);
      bool overwrite = (extractedData.at(1)=="true");
      // check if file needs to be overwritten
      if (overwrite) {
          QFile *existentFile = new QFile(tempDest);
          QFileInfo *info1 = new QFileInfo(wholePath);
          QDateTime datetime1 = info1->lastModified();
          QFileInfo *info2 = new QFileInfo(tempDest);
          QDateTime datetime2 = info2->lastModified();
          if ((existentFile->exists() && datetime1 > datetime2) || !existentFile->exists()) {
            QFile *file = new QFile(wholePath);
            filesize += file->size()/1000000;
          }
      }
      else {
        QFile *file = new QFile(tempDest);
        // just copy the file if it doesn't exist (if it existed it would just give back false and wouldn't copy it)
        if (!file->exists()) {
          QFile *file = new QFile(wholePath);
          filesize += file->size()/1000000;
        }
      }
    }
  }
}

/*
 * Runs the backup.
 *
 * @params:
 *  - QString aSourcePath: the source path
 *  - QString aDestinationPath: the destination path
 *  - QString aOriginalPath: the path which the backup started from
 * @return: none
 */
void Backup::runBackup(QString aSourcePath, QString aDestinationPath, QString aOriginalPath)
{
  // Count all files and filesizes.
  QDir *directory = new QDir(aSourcePath);
  QStringList filesList = directory->entryList(QDir::NoFilter, QDir::DirsFirst);
  progress->setTextVisible(true);
  progress->setRange(0, filesize);
  for (int i = 0; i < filesList.length(); i++) {
    QString temp = filesList.at(i);
    QString wholePath = aSourcePath + "/" + temp;
    if (!temp.compare(".") || !temp.compare(".."))
      continue;

    QString tempDest = aDestinationPath + "/" + temp;
    if (isFolder(wholePath)) {
      QDir *dir = new QDir();
      dir->mkdir(tempDest);
      runBackup(wholePath, tempDest, aOriginalPath);
    }
    else {
      // copy file
      QFile *file = new QFile(wholePath);
      bool copySuccess = file->copy(tempDest);
      // overwrite if option is enabled
      QStringList *lineList = helper->readFile("settings.bs");
      QString tempString = lineList->at(0);
      QStringList extractedData = tempString.split('|', QString::SkipEmptyParts);
      bool overwrite = (extractedData.at(1)=="true");
      if (overwrite) {
        if (!copySuccess) {
          QFile *existentFile = new QFile(tempDest);
          QFileInfo *info1 = new QFileInfo(wholePath);
          QDateTime datetime1 = info1->lastModified();
          QFileInfo *info2 = new QFileInfo(tempDest);
          QDateTime datetime2 = info2->lastModified();
          if (existentFile->exists() && datetime1 > datetime2) {
            existentFile->remove();
            copySuccess = file->copy(tempDest);
          }
        }
      }
      if(copySuccess) {
        currentfilesize += file->size()/1000000;
        progress->setValue(currentfilesize);
        current->setNum(currentfilesize/1.0, 'g', 10);
        size->setText(*current + " MB of " + *total + " MB");
      }
    }
  }
}

/*
 * Checks if the "file" is a folder.
 *
 * @params:
 *  - QString aFileName: the absolute path to the file/folder
 * @return:
 *  - bool : wether the file/folder is a folder
 */
bool Backup::isFolder(QString aFileName)
{
  QDir *dir = new QDir(aFileName);
  return dir->exists();
}
