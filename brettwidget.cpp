#include "brettwidget.h"

#include <QPainter>
#include <QObject>

BrettWidget::BrettWidget()
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

    rasterFarbe = Qt::black;
    hintergrundFarbe = QColor(0,0,0,255);

    brettFarbe = QColor(222,184,135,255);
    weisserStein = QColor(240,240,240,255);;
    schwarzerStein = Qt::black;

    const int size = qMin(this->width(),this->height())-1;
    const int cells = brett.getGroesse();
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
            if (brett.farbe[brett.getPosition(x,y)] == Spielbrett::WEISS)
                painter.drawEllipse(QPoint(cellSize*x + cellSize/2,cellSize*y + cellSize/2),cellSize/2-2,cellSize/2-2);
        }
    }

    painter.setPen(schwarzerStein);
    painter.setBrush(QBrush(schwarzerStein));

    for (int x = 0; x < cells; x++)
    {
        for (int y = 0; y < cells; y++)
        {

            if (brett.farbe[brett.getPosition(x,y)] == Spielbrett::SCHWARZ)
                painter.drawEllipse(QPoint(cellSize*x + cellSize/2,cellSize*y + cellSize/2),cellSize/2-2,cellSize/2-2);
        }
    }
}

