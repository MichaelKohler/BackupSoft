#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QLabel>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QIcon>

class About : public QDialog
{
  Q_OBJECT

  public:
    About();

  private:
    void aboutInit();
};

#endif // ABOUT_H
