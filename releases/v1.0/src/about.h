#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QtGui>

class QAction;

class About : public QDialog
{
  Q_OBJECT

  public:
    About();

  private:
    void aboutInit();
};

#endif // ABOUT_H
