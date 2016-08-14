#ifndef BRETTWIDGET_H
#define BRETTWIDGET_H

#include "spielbrett.h"

#include <QPainter>
#include <QWidget>
#include <QBoxLayout>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <QSound>
#include <QCoreApplication>


class BrettWidget : public QWidget
{
    Q_OBJECT
public:
    BrettWidget();
    void mouseReleaseEvent(QMouseEvent *);




    Spielbrett brett;
    void setAI(Spielbrett::Zellen_Farbe farbe);
    void ZugAI();





signals:
    /** Wird genutzt um dem Spielwindow Objekt zu signalisieren dass eine Veraenderung am Brettwidget stattgefunden hat.
     * @brief brettVeraendert
     */
    void brettVeraendert();
    /** Wird genutzt um zu signalisieren dass auf eine Zelle des Brettwidgets geklickt wurde.
     * @brief zelleGeklickt
     * @param position Die Koordinaten der Zelle auf die geklickt wurde.
     */
    void zelleGeklickt(Spielbrett::SpielPosition position);
    /** Wird genutzt um zu signalisieren dass ein Zug abgeschlossen wurde.
     * @brief zugAusgefuehrt
     */
    void zugAusgefuehrt();

    void checkPass(std::list<Spielbrett::SpielPosition> valideZuege);
private slots:
    /** Wechselt den Style, wenn er im Optionsmenu veraendert wurde und zeichnet das Widget neu.
     * @brief updatedStyle
     * @param style Der neue Style.
     */
    void updatedStyle(int style);
    /** Fuehrt einen Zug auf das geklickte Feld aus (platziert dort einen Stein und dreht andere Steine den Regeln nach um), sofern es einen gueltigen Zug darstellt oder liefert Feedback, falls der Zug ungueltig ist.
     * @brief handleZelleGeklickt
     * @param position Die Position an der ein Stein platziert werden soll.
     */
    void handleZelleGeklickt(Spielbrett::SpielPosition position);
    /** Wechselt die Farbe des Spielers bei zwei Spieler Partien, oder führt den KI Zug aus, sofern die KI aktiviert ist.
     * @brief handleZugAusgefuehrt
     */
    void handleZugAusgefuehrt();

    void handleCheckPass(std::list<Spielbrett::SpielPosition> valideZuege);


private:
   void paintEvent(QPaintEvent *);
   void KIZug();




};

#endif // BRETTWIDGET_H
