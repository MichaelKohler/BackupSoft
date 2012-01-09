#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QPushButton>
#include <QCheckBox>

#include "helper.h"

class QAction;

class Settings : public QDialog
{
  Q_OBJECT

  public:
    Settings();

  public slots:
    void saveSettings();

  private:
    void settingsInit();
    void createActions();

    Helper *helper;

    QPushButton *saveButton;
    QPushButton *closeButton;
    QCheckBox *overwrite;
    QString overwritingString;
};

#endif // SETTINGS_H