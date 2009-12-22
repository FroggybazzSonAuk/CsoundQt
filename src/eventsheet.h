/*
    Copyright (C) 2008, 2009 Andres Cabrera
    mantaraya36@gmail.com

    This file is part of QuteCsound.

    QuteCsound is free software; you can redistribute it
    and/or modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    QuteCsound is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with Csound; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
    02111-1307 USA
*/

#ifndef EVENTSHEET_H
#define EVENTSHEET_H

#include <QTableWidget>
#include <QStandardItemModel>
#include <QAction>

class EventSheet : public QTableWidget
{
  Q_OBJECT
  public:
    EventSheet();
    ~EventSheet();

    QString getPlainText();
    QString getLine(int number);
    void setFromText(QString text);

  public slots:
    void sendEvents();
    void loopEvents();

    void subtract();
    void add();
    void multiply();
    void divide();

    void randomize(double min, double max, int dist);
    void reverse();
    void shuffle(int iterations);
    void mirror();
    void rotate(int amount);
    void fill(double start, double end, double slope);

    void insertColumnHere();
    void insertRowHere();
    void appendColumn();
    void appendRow();
    void deleteColumn();
    void deleteRow();

  protected:
    void contextMenuEvent (QContextMenuEvent * event);

  private:
    void createActions();

    void add(double value);
    void multiply(double value);
    void divide(double value);

    QAction *sendEventsAct;
    QAction *loopEventsAct;
    QAction *stopAllEventsAct;
    QAction *subtractAct;
    QAction *addAct;
    QAction *multiplyAct;
    QAction *divideAct;
    QAction *randomizeAct;
    QAction *reverseAct;
    QAction *shuffleAct;
    QAction *mirrorAct;
    QAction *rotateAct;
    QAction *fillAct;

    QAction *insertColumnHereAct;
    QAction *insertRowHereAct;
    QAction *appendColumnAct;
    QAction *appendRowAct;
    QAction *deleteColumnAct;
    QAction *deleteRowAct;

    QStringList columnNames;

  signals:
    void sendEvent(QString event);
};

#endif // EVENTSHEET_H