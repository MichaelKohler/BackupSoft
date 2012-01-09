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
#include <QDialog>
#include "settings.h"
#include "alertwindow.h"
#include "helper.h"

/*
 * Constructor
 */
Settings::Settings()
{
  helper = new Helper();

  settingsInit();
}

/*
 * initializes the settings window
 *
 * @params: none
 * @return: void
 */
void Settings::settingsInit()
{
  setModal(true);
  setWindowTitle(tr("Settings"));
  setWindowIcon(QIcon("icons/backupsoft.png"));
  resize(300,100);

#ifdef _WIN32
  saveButton = new QPushButton("&Save", this);
  saveButton->setGeometry(90,60,100,30);
#endif

  closeButton = new QPushButton("&Close", this);
  closeButton->setGeometry(190,60,100,30);

  overwrite = new QCheckBox(tr("overwrite older folders"), this);
  overwrite->setGeometry(10,10,200,15);

  createActions();

  QStringList *lineList = helper->readFile("settings.bs");

  // default value
  if (lineList->length() == 0) {
    overwrite->setChecked(true);
  }
  else {
    // read properties
    QStringList prefs;
    for (int i = 0; i < lineList->length(); i++) {
      QString tempString = lineList->at(i);
      QStringList extractedData = tempString.split('|', QString::SkipEmptyParts);
      prefs.append(extractedData[1]);
    }
    overwrite->setChecked(prefs[0]=="true" ? true : false);
  }
}

/*
 * creates the needed actions for the settings window
 *
 * @params: none
 * @return: void
 */
void Settings::createActions()
{
  // Save button only on Windows, directly save on Linux
#ifdef _WIN32
  connect(saveButton, SIGNAL(clicked()), this, SLOT(saveSettings()));
#else
  connect(overwrite, SIGNAL(stateChanged(int)), this, SLOT(saveSettings()));
#endif

  connect(closeButton, SIGNAL(clicked()), this, SLOT(reject())); //Close the Settings Window without saving
}

/*
 *SLOT: Save Settings
 *
 *@params: none
 *@return: void
 */
void Settings::saveSettings()
{
  overwritingString = overwrite->isChecked() ? "true" : "false";
  QString dataString;
  dataString += "overwriting|";
  dataString += overwritingString;
  QByteArray dataBA = dataString.toLatin1();
  helper->writeFile("settings.bs", false, dataBA);

  // only close the settings window after saving on Windows, on Linux it needs a click on the "Close" button
#ifdef _WIN32
  this->close();
#endif
}
