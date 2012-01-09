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
#include "mainwindow.h"
#include "settings.h"
#include "helper.h"

Settings::Settings()
{
  helper = new Helper();

  settingsInit();
}



/*====================WINDOW====================*/

void Settings::settingsInit()
{
  setModal(true);
  setWindowTitle(tr("Settings"));
  setWindowIcon(QIcon("icons/backupsoft.png"));
  resize(350,150);

  restartButton = new QPushButton(tr("&Restart"), this);
  restartButton->hide();

#ifdef _WIN32
  saveButton = new QPushButton(tr("&Save"), this);
  saveButton->setGeometry(140, 110, 100, 30);
  restartButton->setGeometry(10, 110, 100, 30);
#else
  restartButton->setGeometry(140, 110, 100, 30);
#endif

  closeButton = new QPushButton(tr("&Close"), this);
  closeButton->setGeometry(240, 110, 100, 30);

  overwrite = new QCheckBox(tr("overwrite older folders"), this);
  overwrite->setGeometry(10, 10, 200, 15);
  
  languageBox = new QComboBox(this);
  languageBox->setGeometry(10, 40, 150, 25);
  languageBox->addItem("English");
  languageBox->addItem("Deutsch");
  
  lblRestart = new QLabel(tr("A restart will be needed."), this);
  lblRestart->setGeometry(200, 40, 150, 25);
  lblRestart->hide();

  createActions();

  prefs = helper->readProperties();
  if (prefs->at(0) != "")
    overwrite->setChecked((prefs->at(0) == "true") ? true : false);
  else
    overwrite->setChecked(true); // default value

  if (prefs->at(2) != "") {
    bool ok;
    int index = prefs->at(2).toInt(&ok, 10);
    languageBox->setCurrentIndex(index);
  }
  else {
    languageBox->setCurrentIndex(0); // default value
  }
}

void Settings::createActions()
{
  // Save button only on Windows, directly save on Linux
#ifdef _WIN32
  connect(saveButton, SIGNAL(clicked()), this, SLOT(saveSettings()));
#else
  connect(overwrite, SIGNAL(stateChanged(int)), this, SLOT(saveSettings()));
#endif

  connect(languageBox, SIGNAL(currentIndexChanged(int)), this, SLOT(languageIndexChanged()));
  connect(restartButton, SIGNAL(clicked()), this, SLOT(restartApp()));
  connect(closeButton, SIGNAL(clicked()), this, SLOT(reject())); //Close the Settings Window without saving
}



/*====================SLOTS====================*/

void Settings::saveSettings()
{
  overwritingString = overwrite->isChecked() ? "true" : "false";
  QString indexString = "";
  indexString.setNum(languageBox->currentIndex());
  QString dataString;
  dataString += "overwriting|";
  dataString += overwritingString + "\n";
  dataString += "language|";
  dataString += languageBox->currentText().toLower() + "\n";
  dataString += "languageIndex|";
  dataString += indexString;
  QByteArray dataBA = dataString.toLatin1();
  helper->writeFile("settings.bs", false, dataBA);

  // only close the settings window after saving on Windows, on Linux it needs
  // a click on the "Close" button
#ifdef _WIN32
  this->close();
#endif
}

void Settings::languageIndexChanged()
{
  bool ok;
  int initialIndex = prefs->at(2).toInt(&ok, 10);
  if (languageBox->currentIndex() != initialIndex) {
    lblRestart->show();
    restartButton->show();
  }
  else {
    lblRestart->hide();
    restartButton->hide();
  }

#ifndef _WIN32
  // save the settings
  saveSettings();
#endif
}

void Settings::restartApp()
{
  // Code for restart is 1000
  qApp->setQuitOnLastWindowClosed(false);
  qApp->closeAllWindows();
  qApp->exit(1000);
}
