#ifndef BRETTWIDGET_H
#define BRETTWIDGET_H

#include "spielbrett.h"

#include <QPainter>
#include <QWidget>
#include <QBoxLayout>


class BrettWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BrettWidget(QWidget *parent = 0);
    Spielbrett brett;



private:
   void paintEvent(QPaintEvent *);

};

#endif // BRETTWIDGET_H
