#ifndef MINIMAX_H
#define MINIMAX_H

#include <QObject>
#include "spielbrett.h"


class Minimax : public QObject
{
    Q_OBJECT
public:
    /** Konstruktor der Klasse minimax
     * @brief Minimax
     * @param Wurzel das Brett in der auf das der Minimax Algorithmus angewendet werden soll.
     * @param maxTiefe die Suchtiefe des Algorithmus
     */
    Minimax(Spielbrett Wurzel,int maxTiefe);
    virtual ~Minimax();

    /** Methode um den Baum der moeglichen Zuege zu durchlaufen
     * @brief search
     * @return die Bewertung des guenstigsten Zuges
     */
    int search();

    /** Liefert die Koordinaten des guenstigsten Zugs.
     * @brief getBestMove
     * @return Koordinaten der Spielfeldposition an der der guenstigste Zug ausgefuehrt werden kann.
     */
    Spielbrett::SpielPosition getBestMove() const;

private:
    /** Bewertet die moeglichen Zuege und bestimmt den guenstigsten Zug.
     * @brief calculate
     * @param brett Das Spielbrett fuer das der guenstigste Zug bestimmt werden soll.
     * @param depth Die derzeitige Tiefe auf der die zuege bewertet werden.
     * @param alpha Richtwert fuer die bewertung des maximums
     * @param beta  Richtwert fuer die bewertung des minimums
     * @return Die Bewertung des guenstigsten Zuges.
     */
    int calculate(Spielbrett &brett, int depth, int alpha, int beta);
    Spielbrett Wurzel;
    const int maxTiefe;
    Spielbrett::SpielPosition bestMove;
};
#endif // MINIMAX_H
