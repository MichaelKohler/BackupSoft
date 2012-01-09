#ifndef BACKUP_H
#define BACKUP_H

#include <QDialog>
#include <QtGui>

#include "helper.h"

class QAction;

class Backup : public QDialog
{
  Q_OBJECT

  public:
    Backup();
    void initBackup();
  private:
    void initWindow();
    void calcBackup(QString, QString, QString);
    void runBackup(QString, QString, QString);
    bool isFolder(QString);

    unsigned filesize;
    unsigned currentfilesize;
    QLabel *size;
    QPushButton *closeButton;
    QProgressBar *progress;
    QStringList profileInformation;
    QString *total;
    QString *current;

    Helper *helper;
};

#endif // BACKUP_H
