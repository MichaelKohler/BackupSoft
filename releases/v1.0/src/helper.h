#ifndef HELPER_H
#define HELPER_H

#include <QtGui>

class Helper {
  public:
    Helper();
    void writeFile(QString, bool, QByteArray);
    void overwriteFile(QString, QString, bool, QString);
    void deleteProfile(QString, QString);
    QStringList* readFile(QString);
};

#endif // HELPER_H
