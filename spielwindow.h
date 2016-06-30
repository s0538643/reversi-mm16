#ifndef SPIELWINDOW_H
#define SPIELWINDOW_H

#include "brettwidget.h"
#include <QWidget>
#include <QFrame>
#include <QMouseEvent>

class QLabel;

class SpielWindow : public QWidget
{

public:
    SpielWindow();
    BrettWidget *brettwidget;

private:
    QLabel *createLabel(const QString &text);


};

#endif // SPIELWINDOW_H
