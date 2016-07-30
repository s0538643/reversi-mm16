#include "spielwindow.h"
#include <QtWidgets>


SpielWindow::SpielWindow()
{
    brettwidget = new BrettWidget;
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(brettwidget, 0, 1, 6, 1);


    this->Spieler = createLabel(tr("Weiss ist am Zug"));

    this->weissePunkte = createLabel(tr("Weisse Steine: 2"));
    this->schwarzePunkte = createLabel(tr("Schwarze Steine: 2"));

    this->Sieger = createLabel(tr(""));

    layout->addWidget(Spieler, 0, 0);
    layout->addWidget(weissePunkte, 1,0);
    layout->addWidget(schwarzePunkte, 2,0);
    layout->addWidget(Sieger, 3,0);

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

void SpielWindow::updateLabels()
{
    if (this->brettwidget->brett.getSpielerFarbe() == Spielbrett::WEISS)
        Spieler->setText("Weiss ist am Zug");
    else
        Spieler->setText("Schwarz ist am Zug");

    QString weisseSteineZahl = "Weisse Steine: " + QString::number((this->brettwidget->brett.zaehleSteine(Spielbrett::WEISS)));
    weissePunkte->setText(weisseSteineZahl);

    QString schwarzeSteineZahl = "Schwarze Steine: " + QString::number((this->brettwidget->brett.zaehleSteine(Spielbrett::SCHWARZ)));
    schwarzePunkte->setText(schwarzeSteineZahl);

    if (this->brettwidget->brett.getSpielEnde() == true && this->brettwidget->brett.getSieger() == Spielbrett::SCHWARZ)
    {
      Sieger->setText("Schwarz hat gewonnen!");
      QMediaPlayer * blackwin = new QMediaPlayer();
      blackwin->setMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/audio/blackwin.wav"));
      blackwin->play();
    }
    else if (this->brettwidget->brett.getSpielEnde() == true && this->brettwidget->brett.getSieger() == Spielbrett::WEISS)
    {
      Sieger->setText("Weiss hat gewonnen!");
      QMediaPlayer * whitewin = new QMediaPlayer();
      whitewin->setMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/audio/whitewin.wav"));
      whitewin->play();
    }
    else if (this->brettwidget->brett.getSpielEnde() == true && this->brettwidget->brett.getSieger() == Spielbrett::LEER)
        Sieger->setText("Das Spiel endet unentschieden!");
    else if (this->brettwidget->brett.getSpielEnde() == false)
        Sieger->setText("");

}


