#ifndef ALERTWINDOW_H
#define ALERTWINDOW_H

#include <QDialog>

class QAction;

class AlertWindow : public QDialog
{
  Q_OBJECT

  public:
    AlertWindow(QString, QString);
    AlertWindow(QString, QString, QString);
    AlertWindow(QString, QString, QString, QString);

  private:
    void alertInit();
    void createActions();

    QString action;
    QString message;
    QString formOrigin;
    QString profileName;
    
    QPushButton *okButton;
    QPushButton *noButton;
};

#endif // ALERTWINDOW_H
