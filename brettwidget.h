#ifndef BRETTWIDGET_H
#define BRETTWIDGET_H

#include "spielbrett.h"

#include <QPainter>
#include <QWidget>
#include <QBoxLayout>
#include <QMouseEvent>


class BrettWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BrettWidget(QWidget *parent = 0);
    void mouseReleaseEvent(QMouseEvent *);
    Spielbrett brett;

    //Dies ist nur zum testen, LÖSCHEN!!!
    Spielbrett::Zellen_Farbe Spielerfarbe = Spielbrett::WEISS;



private:
   void paintEvent(QPaintEvent *);


};

#endif // BRETTWIDGET_H
