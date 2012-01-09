#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "helper.h"
//#include "backup.h"

class QAction;
class QMenu;
class QMenuBar;
class QPushButton;
class QTableWidget;

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    MainWindow();

  public slots:
    void closeApp();
    void openSettings();
    void openAbout();
    void addProfile();
    void editProfile();
    void deleteProfile();
    void backupNow();
    void updateTable();

  private:
    void initWindow();
    void checkFileExistance();
    void createMenu();
    void createMenuActions();
    void createToolbar();
    void createToolbarActions();
    void createProfileTable();
    void insertProfileData();
    void createBackupButton();
    QString getSelectedProfile();

    Helper *helper;

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *helpMenu;
    QAction *aboutAction;
    QAction *settingsAction;
    QAction *exitAction;
    QAction *addProfileAction;
    QAction *editProfileAction;
    QAction *deleteProfileAction;
    QToolBar *toolBar;
    QPushButton *backupButton;
    QTableWidget *profileTable;

};

#endif
