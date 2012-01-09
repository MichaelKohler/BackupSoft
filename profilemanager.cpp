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
#include "profilemanager.h"
#include "alertwindow.h"
#include "helper.h"

ProfileManager::ProfileManager(QString aSelected) {
  helper = new Helper();

  selectedProfile = aSelected;
}

ProfileManager::ProfileManager(int action)
{
  helper = new Helper();

  origin = action;
  profileInit();
}

ProfileManager::ProfileManager(int action, QString string)
{
  helper = new Helper();

  origin = action;
  profile = string;
  profileInit();
}



/*====================WINDOW====================*/

void ProfileManager::profileInit()
{
  setModal(true);
  resize(370, 170);
  setWindowIcon(QIcon("icons/backupsoft.png"));

  name = new QLabel(tr("Name"), this);
  name->setGeometry(10,10,100,20);
  nameField = new QLineEdit(this);
  nameField->setGeometry(100,10,150,20);

  source = new QLabel(tr("Source"), this);
  source->setGeometry(10,40,100,20);
  sourceField = new QLineEdit(this);
  sourceField->setGeometry(100,40,150,20);

  destination = new QLabel(tr("Destination"), this);
  destination->setGeometry(10,70,100,20);
  destinationField = new QLineEdit(this);
  destinationField->setGeometry(100,70,150,20);

  sourceBrowseButton = new QPushButton(tr("&Browse..."), this);
  sourceBrowseButton->setGeometry(250,40,100,20);
  destinationBrowseButton = new QPushButton(tr("&Browse..."), this);
  destinationBrowseButton->setGeometry(250,70,100,20);

  stateBox = new QCheckBox(tr("Activated"), this);
  stateBox->setGeometry(100, 100, 250, 20);

  cancelButton = new QPushButton(tr("&Cancel"), this);

  if(origin == 1) { // for a new Profile
    setWindowTitle(tr("New Profile"));

    saveButton = new QPushButton(tr("&Save"), this);
    saveButton->setEnabled(false);

    stateBox->setChecked(true); // default
  }

  if(origin == 2) {
    extractedInfo = profile.split('|', QString::SkipEmptyParts);
    setWindowTitle(tr("Edit Profile"));

    saveButton = new QPushButton(tr("&Edit"), this);
    saveButton->setEnabled(true);

    nameField->setText(extractedInfo.value(0));
    sourceField->setText(extractedInfo.value(1));
    destinationField->setText(extractedInfo.value(2));

    bool isActivated = extractedInfo.at(3) == tr("Activated");
    stateBox->setChecked(isActivated);
  }

#ifdef _WIN32
  saveButton->setGeometry(150,130,100,30);
  cancelButton->setGeometry(250,130,100,30);
#else
  saveButton->setGeometry(250,130,100,30);
  cancelButton->setGeometry(150,130,100,30);
#endif

  createActions();
}

void ProfileManager::createActions()
{
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
  connect(saveButton, SIGNAL(clicked()), this, SLOT(saveProfiles()));
  connect(sourceBrowseButton, SIGNAL(clicked()), this, SLOT(browseSrc()));
  connect(destinationBrowseButton, SIGNAL(clicked()), this, SLOT(browseDest()));

  connect(nameField, SIGNAL(textChanged(const QString&)), this, SLOT(checkFilled()));
  connect(sourceField, SIGNAL(textChanged(const QString&)), this, SLOT(checkFilled()));
  connect(destinationField, SIGNAL(textChanged(const QString&)), this, SLOT(checkFilled()));
}



/*====================SLOTS====================*/

void ProfileManager::saveProfiles()
{
  QString name = nameField->text();
  QString src = sourceField->text();
  QString dest = destinationField->text();
  QString state = tr("Deactivated");
  if (stateBox->checkState()) {
    state = tr("Activated");
  }
  // Check wether directory even exists
  QDir *srcDir = new QDir(src);
  QDir *destDir = new QDir(dest);
  if (srcDir->exists() && destDir->exists()) {
    QString dataString = "\n" + name + "|" + src + "|" + dest + "|" + state;
    if(origin == 1) {
      QByteArray dataBA = dataString.toLatin1();
      helper->writeFile("profile.bs", true, dataBA);
    }
    if(origin == 2) {
      QString oldProfile;
      for(int i = 0; i < 4; i++) {
        oldProfile.append(extractedInfo.value(i));
        if(i != 3)
          oldProfile.append('|');
      }
      helper->overwriteFile("profile.bs", oldProfile, true, dataString);
    }
    this->close();
  }
  else {
    QString msg = tr("Either the source or the destination path doesn't exist. Please file it accordingly or create the needed directories.");
    AlertWindow *alertDoesntExist = new AlertWindow("ERROR", msg);
    alertDoesntExist->show();
  }
}

void ProfileManager::browseSrc()
{
  QString directory = QFileDialog::getExistingDirectory(this, tr("Find Files"), QDir::currentPath());

  if (!directory.isEmpty()) {
    sourceField->setText(directory);;
  }
}

void ProfileManager::browseDest()
{
  QString directory = QFileDialog::getExistingDirectory(this, tr("Find Files"), QDir::currentPath());

  if (!directory.isEmpty()) {
    destinationField->setText(directory);;
  }
}

void ProfileManager::doDelete() {
  Helper *helper = new Helper();
  helper->deleteProfile("profile.bs", selectedProfile);
}

void ProfileManager::checkFilled() {
  if (nameField->text() == "" || sourceField->text() == "" || destinationField->text() == "") {
    saveButton->setEnabled(false);
  }
  else {
    saveButton->setEnabled(true);
  }
}
