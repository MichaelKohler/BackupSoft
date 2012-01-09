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
#include "profilemanager.h"
#include "alertwindow.h"
#include "helper.h"

/*
 * Constructor
 */
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

/*
 * initializes the profile window
 *
 * @params: none
 * @return: void
 */
void ProfileManager::profileInit()
{
  setModal(true);
  resize(370, 170);
  setWindowIcon(QIcon("icons/backupsoft.png"));

  name = new QLabel("Name", this);
  name->setGeometry(10,10,100,20);
  nameField = new QLineEdit(this);
  nameField->setGeometry(100,10,150,20);

  source = new QLabel("Source", this);
  source->setGeometry(10,40,100,20);
  sourceField = new QLineEdit(this);
  sourceField->setGeometry(100,40,150,20);

  destination = new QLabel("Destination", this);
  destination->setGeometry(10,70,100,20);
  destinationField = new QLineEdit(this);
  destinationField->setGeometry(100,70,150,20);

  sourceBrowseButton = new QPushButton("&Browse...", this);
  sourceBrowseButton->setGeometry(250,40,100,20);
  destinationBrowseButton = new QPushButton("&Browse...", this);
  destinationBrowseButton->setGeometry(250,70,100,20);

  cancelButton = new QPushButton("&Cancel", this);

  if(origin == 1) { // for a new Profile
    setWindowTitle(tr("New Profile"));

    saveButton = new QPushButton("&Save", this);
    saveButton->setEnabled(false);
  }

  if(origin == 2) {
    extractedInfo = profile.split('|', QString::SkipEmptyParts);
    setWindowTitle(tr("Edit Profile"));

    saveButton = new QPushButton("&Edit", this);
    saveButton->setEnabled(true);

    nameField->setText(extractedInfo.value(0));
    sourceField->setText(extractedInfo.value(1));
    destinationField->setText(extractedInfo.value(2));
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

/*
 * creats the actions
 *
 * @params: none
 * @return: void
 */
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

/*
 * SLOT: Save the profiles in a extern file
 *       with the name profile.bs
 *
 * @params: none
 * @return: void
 */
void ProfileManager::saveProfiles()
{
  QString name = nameField->text();
  QString src = sourceField->text();
  QString dest = destinationField->text();
  QString dataString = name + "|" + src + "|" + dest + "\n";
  if(origin == 1) {
    QByteArray dataBA = dataString.toLatin1();
    helper->writeFile("profile.bs", true, dataBA);
  }
  if(origin == 2) {
    QString oldProfile;
    for(int i = 0; i < 3; i++) {
      oldProfile.append(extractedInfo.value(i));
      if(i != 2)
        oldProfile.append('|');
    }
    helper->overwriteFile("profile.bs", oldProfile, true, dataString);
  }
  this->close();
}

/*
 * SLOT: Open file browser
 *
 * @params: none
 * @return: void
 */
void ProfileManager::browseSrc()
{
  QString directory = QFileDialog::getExistingDirectory(this, tr("Find Files"), QDir::currentPath());

  if (!directory.isEmpty()) {
    sourceField->setText(directory);;
  }
}


/*
 * SLOT: Open file browser
 *
 * @params: none
 * @return: void
 */
void ProfileManager::browseDest()
{
  QString directory = QFileDialog::getExistingDirectory(this, tr("Find Files"), QDir::currentPath());

  if (!directory.isEmpty()) {
    destinationField->setText(directory);;
  }
}

/*
 * SLOT: delete the profile
 *
 * @params: none
 * @return: void
 */
void ProfileManager::doDelete() {
  Helper *helper = new Helper();
  helper->deleteProfile("profile.bs", selectedProfile);
}

/*
 * SLOT: check if all input fields are filled, if so, enable the save/edit button
 *
 * @params: none
 * @return: void
 */
void ProfileManager::checkFilled() {
  if (nameField->text() == "" || sourceField->text() == "" || destinationField->text() == "") {
    saveButton->setEnabled(false);
  }
  else {
    saveButton->setEnabled(true);
  }
}
