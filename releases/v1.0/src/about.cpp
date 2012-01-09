/*
 * Copyright (C) 2010 Fabian Gammenthaler, Michael Kohler
 *
 * BackupSoft is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Contributors:
 *   none
 *
 */
#include "about.h"
#include "alertwindow.h"
#include <QtGui>

/*
 * Constructor
 *
 */
About::About()
{
  aboutInit();
}

void About::aboutInit()
{
  setModal(true);
  resize(400, 400);
  setWindowTitle("About");
  setWindowIcon(QIcon("icons/backupsoft.png"));

  QWidget *icon = new QWidget(this);
  icon->setStyleSheet("background-image: url(icons/backupsoft.png)");
  icon->setGeometry(250 , 10, 100, 100);

  QLabel *title = new QLabel("BackupSoft", this);
  title->setFont(QFont("Helvetica", 25, 10, false));
  title->setGeometry(10, 10, 200, 30);

  QLabel *version = new QLabel("Copyright 2010 by\nMichael Kohler and Fabian Gammenthaler\n\nVersion: 1.0", this);
  version->setFont(QFont("Helvetica", 8, 2, false));
  version->setGeometry(10, 70, 200, 55);

  QTextEdit *licence = new QTextEdit(this);
  licence->setGeometry(10, 160, 380, 230);
  licence->setReadOnly(true);

  QFile *file = new QFile("licence.txt");
  if (file->open(QIODevice::ReadOnly)) {
    QTextStream *stream = new QTextStream(file);
    licence->setText(stream->readAll());
  }
  else {
    QString errorMsg = "Could not open licence.txt.. Please make sure it is existent and readable.";
    AlertWindow *alertWin = new AlertWindow("ERROR", "", errorMsg);
    alertWin->show();
  }
}
