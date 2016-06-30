#include "spielwindow.h"
#include <QtWidgets>


SpielWindow::SpielWindow()
{
    brettwidget = new BrettWidget;
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(brettwidget, 0, 1, 6, 1);

    QLabel *Spieler;
    Spieler = createLabel(tr("Weiss ist am Zug"));
    if (this->brettwidget->Spielerfarbe == Spielbrett::WEISS)
        Spieler->setText("Weiss ist am Zug");
    else
        Spieler->setText("Schwarz ist am Zug");
    layout->addWidget(Spieler, 0, 0);

    layout->setColumnMinimumWidth(0, 200);
    layout->setColumnStretch(1, 1);
    setLayout(layout);


    setWindowTitle(tr("Reversi"));
}

QLabel *SpielWindow::createLabel(const QString &text)
{
    QLabel *lbl = new QLabel(text);
    lbl->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return lbl;
}

