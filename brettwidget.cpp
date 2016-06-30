#include "brettwidget.h"

#include <QPainter>
#include <QObject>
#include <stdio.h>
#include <QDebug>

BrettWidget::BrettWidget(QWidget *parent)
    : QWidget(parent, Qt::Window)

{
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

    valideZuege = this->brett.getValideZuege(this->Spielerfarbe);

    if (valideZuege.empty())
    {


        this->Spielerfarbe = this->brett.getGegnerFarbe(this->Spielerfarbe);

        valideZuege = this->brett.getValideZuege(this->Spielerfarbe); //Spiel endet wenn beide Spieler in folge passen
        if (valideZuege.empty())
            qDebug("Spiel endet"); //HIER SPIEL ENDE EINFÜGEN
    }



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

    if (this->Spielerfarbe == Spielbrett::SCHWARZ)
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
    if(this->brett.Zug(boardPosition, this->Spielerfarbe, true))
    {
        this->Spielerfarbe = this->brett.getGegnerFarbe(this->Spielerfarbe);
    }
    /* else liefere Feedback über unzulässigen Zug
     *
     */
    QString a = QString::number((this->brett.zaehleSteine(Spielbrett::WEISS)));
    qDebug() << a;
    this->update();
}

