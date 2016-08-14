#include "brettwidget.h"


#include <QPainter>
#include <QObject>
#include <stdio.h>
#include <QDebug>
#include "minimax.h"

BrettWidget::BrettWidget(QWidget *parent)
    : QWidget(parent, Qt::Window)

{
    this->brett.setSpielerfarbe(Spielbrett::SCHWARZ);
}

void BrettWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor hintergrundFarbe;
    QColor brettFarbe;
    QColor rasterFarbe;
    QColor weisserStein;
    QColor schwarzerStein;

    std::list<Spielbrett::SpielPosition> valideZuege {}; //hier wird auf gueltige zuege geprueft


    valideZuege = this->brett.getValideZuege(this->brett.getSpielerFarbe());
    emit checkPass(valideZuege);

    int style = this->brett.getBrettstyle();
    rasterFarbe = Qt::black;
    hintergrundFarbe = QColor(0,0,0,255);

    brettFarbe = QColor(222,184,135,255);
    weisserStein = QColor(240,240,240,255);
    schwarzerStein = Qt::black;

    const int size = qMin(this->width(),this->height())-1;
    const int cells = this->brett.getGroesse();
    const int cellSize = size / cells;

    painter.scale(1,-1.0);
    painter.translate(0,-1*size);

    painter.translate((this->width() - cells*cellSize)/2, -1*(this->height() - cells*cellSize)/2);

    painter.fillRect(0,0,cells*cellSize,cells*cellSize,brettFarbe);


    painter.setPen(rasterFarbe);
    for (int x = 0; x <= cells; x++)
    {
        painter.drawLine(x*cellSize,0,x*cellSize,cellSize*cells);
    }

    for (int y = 0; y <= cells; y++)
    {
        painter.drawLine(0,y*cellSize,cellSize*cells,y*cellSize);
    }

    painter.setPen(weisserStein);
    painter.setBrush(QBrush(weisserStein));

    for (int x = 0; x < cells; x++)
    {
        for (int y = 0; y < cells; y++)
        {
            if (this->brett.farbe[this->brett.getPosition(x,y)] == Spielbrett::WEISS)
                switch (style)
                {
                    case 0 :
                    {
                        painter.drawEllipse(QPoint(cellSize*x + cellSize/2,cellSize*y + cellSize/2),cellSize/2-2,cellSize/2-2);
                        break;
                    }



                    case 1 :
                    {
                        QImage image;
                        image.load(":/images/styles/eye-blue.png");
                        painter.drawImage(cellSize*x,cellSize*y, image.scaled(cellSize/1, cellSize/1).mirrored());
                        break;
                    }

                    case 2 :
                    {
                        QImage image;
                        image.load(":/images/styles/White_Viking.png");
                        painter.drawImage(cellSize*x,cellSize*y, image.scaled(cellSize/1, cellSize/1).mirrored());
                    break;
                    }
                }


        }
    }

    painter.setPen(schwarzerStein);
    painter.setBrush(QBrush(schwarzerStein));

    for (int x = 0; x < cells; x++)
    {
        for (int y = 0; y < cells; y++)
        {

            if (this->brett.farbe[this->brett.getPosition(x,y)] == Spielbrett::SCHWARZ)
                switch (style)
                {
                    case 0 :
                    {
                        painter.drawEllipse(QPoint(cellSize*x + cellSize/2,cellSize*y + cellSize/2),cellSize/2-2,cellSize/2-2);
                        break;
                    }

                    case 1 :
                    {
                        QImage image;
                        image.load(":/images/styles/eye-red.png");
                        painter.drawImage(cellSize*x,cellSize*y, image.scaled(cellSize/1, cellSize/1).mirrored());
                        break;
                    }

                    case 2 :
                    {
                        QImage image;
                        image.load(":/images/styles/Black_Viking.png");
                        painter.drawImage(cellSize*x,cellSize*y, image.scaled(cellSize/1, cellSize/1).mirrored());
                        break;
                    }
                }
        }
    }

    if (this->brett.getSpielerFarbe() == Spielbrett::SCHWARZ)
    {
        painter.setPen(schwarzerStein);
        painter.setBrush(QBrush(schwarzerStein));
    }
    else
    {
        painter.setPen(weisserStein);
        painter.setBrush(QBrush(weisserStein));
    }

    for (std::list<Spielbrett::SpielPosition>::const_iterator iterator = valideZuege.begin(), end = valideZuege.end(); iterator != end; ++iterator) {
        painter.drawEllipse(QPoint(cellSize*iterator->x + cellSize/2,cellSize*iterator->y + cellSize/2),cellSize/6-6,cellSize/6-6);
    }
}

void BrettWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();

    const int size = qMin(this->width(),this->height())-1;
    const int cells = this->brett.getGroesse();
    const int cellSize = size / cells;
    QPoint transformedPos = pos;
    transformedPos.setY(transformedPos.y()*-1);
    transformedPos.setY(transformedPos.y() + size);
    transformedPos.setX(transformedPos.x() - (this->width() - cells*cellSize)/2);
    transformedPos.setY(transformedPos.y() + (this->height() - cells*cellSize)/2);


    if (transformedPos.x() < 0 || transformedPos.y() < 0 || transformedPos.x() > cells*cellSize || transformedPos.y() > cells*cellSize)
        return;

    int xCell = transformedPos.x() / cellSize;
    int yCell = transformedPos.y() / cellSize;

    const Spielbrett::SpielPosition boardPosition = {xCell,yCell};

    emit this->zelleGeklickt(boardPosition);
    this->update();

    if (this->brett.getSpielerFarbe() == Spielbrett::WEISS && this->brett.getSchwierigkeit() == 0 && this->brett.getSpielEnde() == false)
    {
        QMediaPlayer * weiss = new QMediaPlayer();
        weiss->setMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/audio/white.wav"));
        weiss->play();
    }
    if (this->brett.getSpielerFarbe() == Spielbrett::SCHWARZ && this->brett.getSchwierigkeit() == 0 && this->brett.getSpielEnde() == false)
    {
        QMediaPlayer * schwarz = new QMediaPlayer();
        schwarz->setMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/audio/black.wav"));
        schwarz->play();
    }

}

void BrettWidget::updatedStyle(int style)
{
    this->brett.setBrettstyle(style);
    this->update();
}

void BrettWidget::handleZelleGeklickt(Spielbrett::SpielPosition position)
{
    if (this->brett.Zug(position, this->brett.getSpielerFarbe(), 1) == true)
    {

        this->zugAusgefuehrt();


    }
    else {

        QMediaPlayer * fail = new QMediaPlayer();
        fail->setMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/audio/fail.wav"));
        fail ->play();
    }


}

void BrettWidget::handleZugAusgefuehrt()
{
    this->brett.setSpielerfarbe(this->brett.getGegnerFarbe(this->brett.getSpielerFarbe()));

    emit this->brettVeraendert();

    if (this->brett.getSchwierigkeit() != 0)
    {
        this->KIZug();
    }
}

void BrettWidget::KIZug()
{
   // this->brett.setSpielerfarbe(Spielbrett::SCHWARZ);
    this->brett.calculateBestMove(this->brett.getSpielerFarbe(), this->brett.getSchwierigkeit());
    QVariant var(this->brett.getBestMove().x);
        QString stringValue = var.toString();
        qDebug() << "x-Wert:"+stringValue;

    QVariant vaar(this->brett.getBestMove().y);
            QString stringValuee = vaar.toString();
            qDebug() << "y-Wert:"+stringValuee;


    if( this->brett.Zug(this->brett.getBestMove(), this->brett.getSpielerFarbe(), 1))
    {
        this->brett.setSpielerfarbe(this->brett.getGegnerFarbe(this->brett.getSpielerFarbe()));
        emit this->brettVeraendert();
    }

}

void BrettWidget::handleCheckPass(std::list<Spielbrett::SpielPosition> valideZuege)
{
    if(valideZuege.empty())
    {
        valideZuege = this->brett.getValideZuege(this->brett.getGegnerFarbe(this->brett.getSpielerFarbe()));
        if(valideZuege.empty())
        {
            this->brett.setSpielEnde(true);
            emit this->brettVeraendert();
        }
        else
        {
            this->zugAusgefuehrt();
            update();
        }
}
}

