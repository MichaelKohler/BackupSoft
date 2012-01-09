#ifndef HELPER_H
#define HELPER_H

#include <QDialog>
#include <QtGui>

class Helper {
  Q_DECLARE_TR_FUNCTIONS(Helper)

  public:
    Helper();
    void writeFile(QString, bool, QByteArray);
    void overwriteFile(QString, QString, bool, QString);
    void deleteProfile(QString, QString);
    QStringList* readProperties();
    QStringList* readFile(QString);
};

#endif // HELPER_H
