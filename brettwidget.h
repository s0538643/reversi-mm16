#ifndef BRETTWIDGET_H
#define BRETTWIDGET_H

#include "spielbrett.h"
#include <QPainter>
#include <QWidget>

class BrettWidget : public QWidget
{
public:
    BrettWidget();
    Spielbrett brett;
private:
    void paintEvent(QPaintEvent *);

};

#endif // BRETTWIDGET_H
