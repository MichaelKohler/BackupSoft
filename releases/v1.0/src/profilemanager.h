#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include <QDialog>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QString>

#include "helper.h"

class QAction;

class ProfileManager : public QDialog
{
  Q_OBJECT

  public:
    ProfileManager(QString);
    ProfileManager(int);
    ProfileManager(int, QString);

  public slots:
    void saveProfiles();
    void browseSrc();
    void browseDest();
    void doDelete();
    void checkFilled();

  private:
    void profileInit();
    void createActions();

    Helper *helper;

    QPushButton *saveButton;
    QPushButton *cancelButton;
    QPushButton *sourceBrowseButton;
    QPushButton *destinationBrowseButton;
    QLabel *overwrite;
    QLabel *name;
    QLabel *source;
    QLabel *destination;
    QLineEdit *nameField;
    QLineEdit *sourceField;
    QLineEdit *destinationField;
    QComboBox *directoryComboBox;
    QString profile;
    QString selectedProfile;
    QStringList extractedInfo;
    int origin;
};

#endif // PROFILEMANAGER_H
