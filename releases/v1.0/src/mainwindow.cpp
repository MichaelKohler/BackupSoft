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
#include "mainwindow.h"
#include "settings.h"
#include "profilemanager.h"
#include "alertwindow.h"
#include "helper.h"
#include "backup.h"
#include "about.h"

/*
 * Constructor
 */
MainWindow::MainWindow()
{
  helper = new Helper();

  checkFileExistance();
  initWindow();
}

/*
 * checks if the needed files are existent. if not, it creates them
 *
 * @params: none
 * @return: void
 */
void MainWindow::checkFileExistance() {
  QFile *profileFile = new QFile("profile.bs");
  if (!profileFile->exists()) {
    profileFile->open(QIODevice::ReadWrite);
    profileFile->close();
  }

  QFile *settingsFile = new QFile("settings.bs"); // this file is not yet used
  if (!settingsFile->exists()) {
    QString settings = "overwrite|true";
    QByteArray data = settings.toLatin1();
    helper->writeFile("settings.bs", false, data);
  }
}

/*
 * initializes the main window.
 *
 * @params: none
 * @return: void
 */
void MainWindow::initWindow()
{
  resize(600, 350);
  setWindowTitle(tr("BackupSoft"));
  setWindowIcon(QIcon("icons/backupsoft.png"));
  createMenu();
  createToolbar();
  createProfileTable();
  createBackupButton();
}

/*
 * creates the menubar
 *
 * @params: none
 * @return: void
 */
void MainWindow::createMenu()
{
  createMenuActions();

  menuBar = new QMenuBar;

  fileMenu = new QMenu(tr("&File"), this);
  fileMenu->addAction(settingsAction);
  fileMenu->addAction(exitAction);
  menuBar->addMenu(fileMenu);

  helpMenu = new QMenu(tr("&Help"), this);
  helpMenu->addAction(aboutAction);
  menuBar->addMenu(helpMenu);

  setMenuBar(menuBar);
}

/*
 * creates the actions for the menu
 *
 * @params: none
 * @return: void
 */
void MainWindow::createMenuActions()
{
  exitAction = new QAction(tr("&Exit"), this);
  exitAction->setShortcut(tr("Ctrl+Q"));
  exitAction->setStatusTip(tr("Exit the application"));
  connect(exitAction, SIGNAL(triggered()), this, SLOT(closeApp()));

  settingsAction = new QAction(tr("&Settings"), this);
  settingsAction->setShortcut(tr("Ctrl+E"));
  settingsAction->setStatusTip(tr("Open the settings window"));
  connect(settingsAction, SIGNAL(triggered()), this, SLOT(openSettings()));

  aboutAction = new QAction(tr("&About BackupSoft"), this);
  aboutAction->setStatusTip(tr("Open the about window"));
  connect(aboutAction, SIGNAL(triggered()), this, SLOT(openAbout()));
}

/*
 * creates the mainwindow's toolbar
 *
 * @params: none
 * @return: void
 */
void MainWindow::createToolbar()
{
  createToolbarActions();

  toolBar = addToolBar(tr("toolbar"));
  toolBar->setMovable(false);
  toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  toolBar->addAction(addProfileAction);
  toolBar->addSeparator();
  toolBar->addAction(editProfileAction);
  toolBar->addSeparator();
  toolBar->addAction(deleteProfileAction);
}

/*
 * creates the actions for the toolbar
 *
 * @params: none
 * @return: void
 */
void MainWindow::createToolbarActions()
{
  addProfileAction = new QAction(tr("&Add"), this);
  addProfileAction->setStatusTip(tr("Add a profile"));
  addProfileAction->setIcon(QIcon("icons/add.png"));
  connect(addProfileAction, SIGNAL(triggered()), this, SLOT(addProfile()));

  editProfileAction = new QAction(tr("&Edit"), this);
  editProfileAction->setStatusTip(tr("Edit the selected profile"));
  editProfileAction->setIcon(QIcon("icons/edit.png"));
  connect(editProfileAction, SIGNAL(triggered()), this, SLOT(editProfile()));

  deleteProfileAction = new QAction(tr("&Delete"), this);
  deleteProfileAction->setStatusTip(tr("Delete the selected profile"));
  deleteProfileAction->setIcon(QIcon("icons/delete.png"));
  connect(deleteProfileAction, SIGNAL(triggered()), this, SLOT(deleteProfile()));
}

/*
 * creates the table for the profiles
 *
 * @params: none
 * @return: void
 */
void MainWindow::createProfileTable()
{
  profileTable = new QTableWidget(0, 3);
  QStringList labels;
  labels << tr("Profilename") << tr("Source") << tr("Destination");
  profileTable->setHorizontalHeaderLabels(labels);
  profileTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
  profileTable->setGeometry(20, 75, 550, 200);
  profileTable->horizontalHeader()->resizeSection(0, 100);
  profileTable->horizontalHeader()->resizeSection(1, 225);
  profileTable->horizontalHeader()->resizeSection(2, 225);
  profileTable->verticalHeader()->hide();
  profileTable->setShowGrid(false);
  insertProfileData();

  profileTable->setParent(this);
}

/*
 * inserts the data into the table
 *
 * @params: none
 * @return: void
 */
void MainWindow::insertProfileData()
{
  // read the profiles from the file
  QStringList *lineList = helper->readFile("profile.bs");

  // message when profiles file is empty
  if (lineList->length() == 0) {
    int row = profileTable->rowCount();
    profileTable->insertRow(row);
    QString entryValue = "No profile created.";
    QTableWidgetItem *noProfileEntry = new QTableWidgetItem(entryValue);
    noProfileEntry->setFlags(Qt::ItemIsEnabled);
    noProfileEntry->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    noProfileEntry->setToolTip(entryValue);
    profileTable->setItem(row, 0, noProfileEntry);
  }

  // for iteration for the rows
  for (int i = 0; i < lineList->length(); i++) {
    QString tempString = lineList->at(i);
    QStringList extractedData = tempString.split('|', QString::SkipEmptyParts);
    int row = profileTable->rowCount();
    profileTable->insertRow(row);
    // for iteration for the different columns of the row
    for (int j = 0; j < 3; j++) {
      QString entryValue = extractedData.at(j);
      QTableWidgetItem *entry = new QTableWidgetItem(entryValue);
      entry->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
      entry->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
      entry->setToolTip(entryValue);
      profileTable->setItem(row, j, entry);
    }
  }
}

/*
 * creates the "Backup Now" button
 *
 * @params: none
 * @return: void
 */
void MainWindow::createBackupButton()
{
  backupButton = new QPushButton("&Backup Now!", this);
  backupButton->setGeometry(440,300,130,35);
  backupButton->setIcon(QIcon("icons/backup.png"));
  connect(backupButton, SIGNAL(clicked()), this, SLOT(backupNow()));
}

/*
 * SLOT: closes the backupsoft application
 *
 * @params: none
 * @return: void
 */
void MainWindow::closeApp()
{
  qApp->closeAllWindows();
}

/*
 * SLOT: opens the settings window
 *
 * @params: none
 * @return: void
 */
void MainWindow::openSettings()
{
  Settings settingsWin;
  settingsWin.show();
  settingsWin.exec();
}

/*
 * SLOT: adds a profile
 *
 * @params: none
 * @return: void
 */
void MainWindow::addProfile()
{
  ProfileManager profileWin(1);
  profileWin.show();
  profileWin.exec();
  insertProfileData();
  updateTable();
}

/*
 * SLOT: opens the about Window
 *
 * @params: none
 * @return: void
 */
void MainWindow::openAbout()
{
  About aboutWin;
  aboutWin.show();
  aboutWin.exec();
}

/*
 * SLOT: edits the selected profile
 *
 * @params: none
 * @return: void
 */
void MainWindow::editProfile()
{  
  QString profile;
  profile = getSelectedProfile();
  if(profile == "") {
    QString errorMsg = "No profile selected! Please select one.";
    AlertWindow *alertWin = new AlertWindow("ERROR", "", errorMsg);
    alertWin->show();
  }
  else {
    ProfileManager profileWin(2, profile);
    profileWin.show();
    profileWin.exec();
    updateTable();
  }
}

/*
 * SLOT: "deletes" the selected profile (doesn't delete it, just shows the alert window;
 *          selected profile needs to be passed)
 *
 * @params: none
 * @return: void
 */
void MainWindow::deleteProfile()
{
  QString profile;
  QStringList profileName;
  QString msg;
  profile = getSelectedProfile();
  if(profile.isEmpty()) {
    AlertWindow *alWin = new AlertWindow ("ERROR", "", "No profile selected! Please select one.");
    alWin->show();
  }
  else {
    profileName = profile.split("|", QString::SkipEmptyParts);
    msg = "Do you really want to delete the \"" + profileName.value(0) + "\" profile?";
    AlertWindow *alertWin = new AlertWindow("QUESTION", "PROFILE", msg, profile);
    alertWin->show();
    alertWin->exec();
    updateTable();
  }
}

/*
 * SLOT: starts the backup
 *
 * @params: none
 * @return: void
 */
void MainWindow::backupNow()
{
  Backup backupWin;
  backupWin.show();
  backupWin.initBackup();
  backupWin.exec();
}

/*
 * Updates the tableentries
 *
 *@params: none
 *@return: void
 */
void MainWindow::updateTable()
{
  for (int i = profileTable->rowCount() - 1; i >= 0; --i)
    profileTable->removeRow(i);

  createProfileTable();
  insertProfileData();

  for (int i = profileTable->rowCount()/2 - 1; i >= 0; --i)
    profileTable->removeRow(i);

  profileTable->show();
}

/*
 * Read the selected item
 *
 * @params: none
 * @return: QString
 */
QString MainWindow::getSelectedProfile()
{
  QList<QTableWidgetItem* > list;
  QString profile = "";
  int row;
  int column;
  int pos = 0;

  list.append(profileTable->selectedItems());
  if(list.length() == 0) {
    profile = "";
    return profile;
  }
  else {
    row = list.value(pos)->row();
    for(column = 0; column < 3 ; column++)
    {
      profile.append(profileTable->item(row, column)->text());
      if(column != 2)
        profile.append("|");
    }
    return profile;
  }
}
