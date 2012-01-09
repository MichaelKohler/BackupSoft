#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>

#include "helper.h"

class QAction;

class Settings : public QDialog
{
  Q_OBJECT

  public:
    Settings();

  public slots:
    void saveSettings();
    void languageIndexChanged();
    void restartApp();

  private:
    void settingsInit();
    void createActions();

    Helper *helper;

    QPushButton *restartButton;
    QPushButton *saveButton;
    QPushButton *closeButton;
    QCheckBox *overwrite;
    QComboBox *languageBox;
    QString overwritingString;
    QLabel *lblRestart;
    QStringList *prefs;
};

#endif // SETTINGS_H
