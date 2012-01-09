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

#include <QApplication>
#include <QDialog>
#include "mainwindow.h"
#include "settings.h"
#include "profilemanager.h"
#include "alertwindow.h"
#include "helper.h"
#include "backup.h"
#include "about.h"


/*====================MAIN METHOD====================*/
/*=================APPLICATION ENTRY=================*/

#define RESTART_CODE 1000
int main(int argc, char *argv[])
{
  int return_from_event_loop_code;
  do
  {
    QApplication *app = new QApplication(argc, argv);
    app->setQuitOnLastWindowClosed(true);
 
    Helper *helper = new Helper();
    QStringList *prefs = helper->readProperties();
    QTranslator translator;
    if (prefs->at(2) != "0") {
      QString translationFile = prefs->at(1) + ".qm";
      translator.load(QString(translationFile));
      app->installTranslator(&translator);
    }
 
    MainWindow *mainwindow = new MainWindow();
    mainwindow->show();
    return_from_event_loop_code = app->exec(); // if return code is 1000, restart app
  }
  while(return_from_event_loop_code==RESTART_CODE);
 
  return return_from_event_loop_code;
}
/*====================MAIN END====================*/
/*=================APPLICATION EXIT=================*/

MainWindow::MainWindow()
{
  helper = new Helper();

  checkFileExistance();
  initWindow();
}

void MainWindow::checkFileExistance() {
  QFile *profileFile = new QFile("profile.bs");
  if (!profileFile->exists()) {
    profileFile->open(QIODevice::ReadWrite);
    profileFile->close();
  }

  QFile *settingsFile = new QFile("settings.bs");
  if (!settingsFile->exists()) {
    QString settings = "overwrite|true";
    QByteArray data = settings.toLatin1();
    helper->writeFile("settings.bs", false, data);
  }
}



/*====================MAINWINDOW====================*/

void MainWindow::initWindow()
{
  setMinimumSize(600,350); // HACK: need to find a better way..
  setMaximumSize(600,350);
  setWindowTitle(tr("BackupSoft"));
  setWindowIcon(QIcon("icons/backupsoft.png"));
  createMenu();
  createToolbar();
  createProfileTable();
  createBackupButton();
}

void MainWindow::createMenu()
{
  createMenuActions();

  menuBar = new QMenuBar;

  fileMenu = new QMenu(tr("&File"), this);
  fileMenu->addAction(backupAction);
  fileMenu->addAction(settingsAction);
  fileMenu->addAction(exitAction);
  menuBar->addMenu(fileMenu);

  helpMenu = new QMenu(tr("&Help"), this);
  helpMenu->addAction(aboutAction);
  menuBar->addMenu(helpMenu);

  setMenuBar(menuBar);
}

void MainWindow::createMenuActions()
{
  backupAction = new QAction(tr("&Backup Now"), this);
  backupAction->setShortcut(tr("Ctrl+B"));
  backupAction->setStatusTip(tr("Starts the Backup"));
  connect(backupAction, SIGNAL(triggered()), this, SLOT(backupNow()));

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

void MainWindow::createBackupButton()
{
  backupButton = new QPushButton(tr("&Backup Now!"), this);
  backupButton->setGeometry(440,300,130,35);
  backupButton->setIcon(QIcon("icons/backup.png"));
  connect(backupButton, SIGNAL(clicked()), this, SLOT(backupNow()));
}



/*====================PROFILE TABLE====================*/

void MainWindow::createProfileTable()
{
  profileTable = new QTableWidget(0, 4);
  QStringList labels;
  labels << tr("Profilename") << tr("Source") << tr("Destination") << tr("Active");
  profileTable->setHorizontalHeaderLabels(labels);
  profileTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
  profileTable->setSelectionBehavior(QAbstractItemView::SelectRows);
  profileTable->setSelectionMode(QAbstractItemView::SingleSelection);
  profileTable->setGeometry(20, 75, 550, 200);
  profileTable->setSortingEnabled(true);
  profileTable->sortItems(3, Qt::AscendingOrder);
  profileTable->horizontalHeader()->resizeSection(0, 95);
  profileTable->horizontalHeader()->resizeSection(1, 190);
  profileTable->horizontalHeader()->resizeSection(2, 190);
  profileTable->horizontalHeader()->resizeSection(3, 75);
  profileTable->verticalHeader()->hide();
  profileTable->setShowGrid(false);
  insertProfileData();

  profileTable->setParent(this);
}

void MainWindow::insertProfileData()
{
  // read the profiles from the file
  QStringList *lineList = helper->readFile("profile.bs");

  // message when profiles file is empty
  if (lineList->length() == 0) {
    int row = profileTable->rowCount();
    profileTable->insertRow(row);
    QString entryValue = tr("No profile created.");
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
    for (int j = 0; j < 4; j++) {
      QString entryValue = tr("%1").arg(extractedData.at(j));
      QTableWidgetItem *entry = new QTableWidgetItem(entryValue);
      entry->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
      entry->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
      entry->setToolTip(entryValue);
      profileTable->setItem(row, j, entry);
    }
  }
}

void MainWindow::updateTable()
{
  int rows = profileTable->rowCount();
  for (int i = 0; i < rows; i++)
    profileTable->removeRow(i);

  createProfileTable();

  profileTable->show();
}

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
    for(column = 0; column < 4; column++)
    {
      profile.append(profileTable->item(row, column)->text());
      if(column != 3)
        profile.append("|");
    }
    return profile;
  }
}



/*====================SLOTS====================*/

void MainWindow::backupNow()
{
  Backup backupWin;
  backupWin.show();
  backupWin.initBackup();
  backupWin.exec();
}

void MainWindow::closeApp()
{
  qApp->closeAllWindows();
}

void MainWindow::openSettings()
{
  Settings settingsWin;
  settingsWin.show();
  settingsWin.exec();
}

void MainWindow::openAbout()
{
  About aboutWin;
  aboutWin.show();
  aboutWin.exec();
}

void MainWindow::addProfile()
{
  ProfileManager profileWin(1);
  profileWin.show();
  profileWin.exec();
  insertProfileData();
  updateTable();
}

void MainWindow::editProfile()
{  
  QString profile;
  profile = getSelectedProfile();
  if(profile == "") {
    QString msg = tr("No profile selected! Please select one.");
    AlertWindow *alertWin = new AlertWindow("ERROR", msg);
    alertWin->show();
  }
  else {
    ProfileManager profileWin(2, profile);
    profileWin.show();
    profileWin.exec();
    updateTable();
  }
}

void MainWindow::deleteProfile()
{
  QString profile;
  QStringList profileName;
  profile = getSelectedProfile();
  if(profile.isEmpty()) {
    QString msg = tr("No profile selected! Please select one.");
    AlertWindow *alWin = new AlertWindow("ERROR", msg);
    alWin->show();
  }
  else {
    profileName = profile.split("|", QString::SkipEmptyParts);
    QString msg = tr("Do you really want to delete the %1 profile?").arg(profileName.value(0));
    AlertWindow *alertWin = new AlertWindow("QUESTION", "PROFILE", msg, profile);
    alertWin->show();
    alertWin->exec();
    updateTable();
  }
}
