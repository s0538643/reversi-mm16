#include "spielwindow.h"
#include <QtWidgets>


SpielWindow::SpielWindow()
{
        brettwidget = new BrettWidget;
}

SpielWindow::SpielWindow(QString name1, QString name2, Spielbrett::Zellen_Farbe spielerfarbe, int sprache)
{
    this->sprache = sprache;
    brettwidget = new BrettWidget;
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(brettwidget, 0, 1, 6, 1);
    this->weissname = name1;
    this->schwarzname = name2;
    if (spielerfarbe == 1 && sprache == 0)
        this->Spieler = createLabel(this->weissname + " ist am Zug");
    else if (spielerfarbe == 1 && sprache == 1)
        this->Spieler = createLabel(this->weissname + "'s turn");
    else if (spielerfarbe == 2 && sprache == 0)
        this->Spieler = createLabel(this->schwarzname + " ist am Zug");
    else if (spielerfarbe == 2 && sprache == 1)
        this->Spieler = createLabel(this->schwarzname + "'s turn");

    if (sprache == 0)
    {
        this->weissePunkte = createLabel(tr("Weisse Steine: 2"));
        this->schwarzePunkte = createLabel(tr("Schwarze Steine: 2"));
    }
    else if (sprache == 1)
    {
        this->weissePunkte = createLabel(tr("White discs: 2"));
        this->schwarzePunkte = createLabel(tr("Black discs: 2"));
    }

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

SpielWindow::~SpielWindow()
{
    if (brettwidget != NULL)
        delete brettwidget;
}


QLabel *SpielWindow::createLabel(const QString &text)
{
    QLabel *lbl = new QLabel(text);
    lbl->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return lbl;
}

void SpielWindow::updateLabels()
{
    QString weisseSteineZahl;
    QString schwarzeSteineZahl;
    if (this->brettwidget->brett.getSpielerFarbe() == Spielbrett::WEISS && this->sprache == 0)
        Spieler->setText(this->weissname + " ist am Zug");
    else if (this->brettwidget->brett.getSpielerFarbe() == Spielbrett::SCHWARZ && this->sprache == 0)
        Spieler->setText(this->schwarzname + " ist am Zug");
    else if (this->brettwidget->brett.getSpielerFarbe() == Spielbrett::WEISS && this->sprache == 1)
        Spieler->setText(this->weissname + "'s turn");
    else if (this->brettwidget->brett.getSpielerFarbe() == Spielbrett::SCHWARZ && this->sprache == 1)
        Spieler->setText(this->schwarzname + "'s turn");
    if (this->sprache == 0)
       weisseSteineZahl = "Weisse Steine: " + QString::number((this->brettwidget->brett.zaehleSteine(Spielbrett::WEISS)));
    else
         weisseSteineZahl = "White Discs: " + QString::number((this->brettwidget->brett.zaehleSteine(Spielbrett::WEISS)));

    weissePunkte->setText(weisseSteineZahl);

    if (this->sprache == 0)
        schwarzeSteineZahl = "Schwarze Steine: " + QString::number((this->brettwidget->brett.zaehleSteine(Spielbrett::SCHWARZ)));
    else
        schwarzeSteineZahl = "Black Discs: " + QString::number((this->brettwidget->brett.zaehleSteine(Spielbrett::SCHWARZ)));
    schwarzePunkte->setText(schwarzeSteineZahl);

    if (this->brettwidget->brett.getSpielEnde() == true && this->brettwidget->brett.getSieger() == Spielbrett::SCHWARZ && this->sprache == 0)
    {
      Sieger->setText(this->schwarzname + " hat gewonnen!");
      QMediaPlayer * blackwin = new QMediaPlayer();
      blackwin->setMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/audio/blackwin.wav"));
      blackwin->play();
    }
    else if (this->brettwidget->brett.getSpielEnde() == true && this->brettwidget->brett.getSieger() == Spielbrett::SCHWARZ && this->sprache == 1)
    {
        Sieger->setText(this->schwarzname + " is the winner!");
        QMediaPlayer * blackwin = new QMediaPlayer();
        blackwin->setMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/audio/blackwin.wav"));
        blackwin->play();
    }
    else if (this->brettwidget->brett.getSpielEnde() == true && this->brettwidget->brett.getSieger() == Spielbrett::WEISS && this->sprache == 0)
    {
      Sieger->setText(this->weissname + " hat gewonnen!");
      QMediaPlayer * whitewin = new QMediaPlayer();
      whitewin->setMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/audio/whitewin.wav"));
      whitewin->play();
    }
    else if (this->brettwidget->brett.getSpielEnde() == true && this->brettwidget->brett.getSieger() == Spielbrett::WEISS && this->sprache == 1)
    {
      Sieger->setText(this->weissname + " is the winner!");
      QMediaPlayer * whitewin = new QMediaPlayer();
      whitewin->setMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/audio/whitewin.wav"));
      whitewin->play();
    }
    else if (this->brettwidget->brett.getSpielEnde() == true && this->brettwidget->brett.getSieger() == Spielbrett::LEER && this->sprache == 0)
        Sieger->setText("Das Spiel endet unentschieden!");
    else if (this->brettwidget->brett.getSpielEnde() == true && this->brettwidget->brett.getSieger() == Spielbrett::LEER && this->sprache == 1)
        Sieger->setText("The game ends in a draw!");
    else if (this->brettwidget->brett.getSpielEnde() == false)
        Sieger->setText("");

}


