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
#include "alertwindow.h"
#include "profilemanager.h"

/*
 * Constructor
 *
 * @params:
 *    - aAction = "ERROR", "WARNING" or "QUESTION" (NEEDS TO BE SET!)
 *    - aOrigin = Window that sent the alert (either "PROFILE" or "ABORT" or "")
 *    - aMessage = Message to display in the alert window
 */
AlertWindow::AlertWindow(QString aAction, QString aOrigin, QString aMessage)
{
  action = aAction;
  message = aMessage;
  formOrigin = aOrigin;
  alertInit();
}

/*
 * Constructor
 *
 * @params:
 *    - aAction = "ERROR", "WARNING" or "QUESTION" (NEEDS TO BE SET!)
 *    - aOrigin = Window that sent the alert (either "PROFILE" or "ABORT" or "")
 *    - aMessage = Message to display in the alert window
 *    - aProfile = The profile which has to be deleted
 */
AlertWindow::AlertWindow(QString aAction, QString aOrigin, QString aMessage, QString aProfile )
{
  action = aAction;
  message = aMessage;
  formOrigin = aOrigin;
  profileName = aProfile;
  alertInit();
}

/*
 * initializes the alert window
 *
 * @params: none
 * @return: void
 */
void AlertWindow::alertInit()
{
  setModal(true);
  resize(350,150);
  setWindowTitle(action); // WARNING, ERROR, QUESTION
  if (action == "WARNING")
    setWindowIcon(QIcon("icons/warning.png"));
  else if (action == "ERROR")
    setWindowIcon(QIcon("icons/error.png"));
  else
    setWindowIcon(QIcon("icons/question.png"));

  QLabel *warningText = new QLabel(message);
  warningText->setGeometry(130, 0, 200, 110);
  warningText->setWordWrap(true);
  warningText->setParent(this);

  if (action == "QUESTION") {
    okButton = new QPushButton("&Yes", this);
    okButton->setGeometry(100, 110, 60, 30);

    noButton = new QPushButton("&No", this);
    noButton->setGeometry(190, 110, 60, 30);

    QWidget *icon = new QWidget(this);
    icon->setStyleSheet("background-image: url(icons/question.png)");
    icon->setGeometry(5, 10, 96, 96);
  }
  else {
    okButton = new QPushButton("&OK", this);
    okButton->setGeometry(145, 110, 60, 30);
  }

  if (action == "ERROR") {
    QWidget *icon = new QWidget(this);
    icon->setStyleSheet("background-image: url(icons/error.png)");
    icon->setGeometry(5, 10, 96, 96);
  }
  else if (action == "WARNING") {
    QWidget *icon = new QWidget(this);
    icon->setStyleSheet("background-image: url(icons/warning.png)");
    icon->setGeometry(5, 10, 96, 96);
  }

  createActions();
}

/*
 * creates the needed actions for the alert window
 *
 * @params: none
 * @return: void
 */
void AlertWindow::createActions()
{
  if (action != "QUESTION") {
    connect(okButton, SIGNAL(clicked()), this, SLOT(reject()));
  }
  else {
    if (formOrigin == "PROFILE") {
      // continue delete
      QString selectedProfile = profileName;
      ProfileManager *profMan = new ProfileManager(selectedProfile);
      connect(okButton, SIGNAL(clicked()), profMan, SLOT(doDelete())); // delete the profile
      connect(okButton, SIGNAL(clicked()), this, SLOT(reject())); // close the alert window
    }

    connect(noButton, SIGNAL(clicked()), this, SLOT(reject()));
  }
}
