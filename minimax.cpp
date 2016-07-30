#include "minimax.h"

#include <QList>
#include <QCoreApplication>
#include <QtDebug>


Minimax::Minimax(Spielbrett Wurzel,int maxTiefe) :
        Wurzel(Wurzel), maxTiefe(maxTiefe)
{
    Spielbrett::SpielPosition bestMove = {0,0};
    this->bestMove = bestMove;
}

Minimax::~Minimax()
{

}

int Minimax::search()
{
    return calculate(this->Wurzel,0,-10000,10000);

}

int Minimax::calculate(Spielbrett brett, int tiefe, int alpha, int beta)
{

    Spielbrett::Zellen_Farbe naechsterSpieler = brett.getSpielerFarbe();
    std::list<Spielbrett::SpielPosition> alleZuege = brett.getValideZuege(naechsterSpieler);

    if (++tiefe > this->maxTiefe) { //maximale Suchtiefe erreicht
        return 0;
    }
    else
        tiefe++;

    for (std::list<Spielbrett::SpielPosition>::const_iterator iterator = alleZuege.begin(), end = alleZuege.end(); iterator != end; ++iterator)
    {
       Spielbrett simBrett;

       Spielbrett::SpielPosition derzeitigerZug = {iterator->x, iterator->y};
       simBrett.Zug(derzeitigerZug, naechsterSpieler, 1);

        int score = this->calculate(simBrett, tiefe,alpha,beta);
        bestMove = {iterator->x,iterator->y};
        if (naechsterSpieler == Spielbrett::WEISS)
        {
            if (score > alpha)
            {
                alpha = score;
                bestMove = derzeitigerZug;
            }
            else if (score == alpha && qrand() % 2) {
                bestMove = derzeitigerZug;
            }

            if (beta <= alpha) {
                break;
            }
        }
        else if (naechsterSpieler == Spielbrett::SCHWARZ)
        {
            if (score < beta)
            {
                beta = score;
                bestMove = derzeitigerZug;
            }
            else if (score == beta && qrand() % 2) {
                bestMove = derzeitigerZug;
            }

            if (beta <= alpha) {
                break;
            }
        }
    }

   this->bestMove = bestMove;



    if (naechsterSpieler == Spielbrett::WEISS) {
        return alpha;
    }
    else {
        return beta;
    }

}


Spielbrett::SpielPosition Minimax::getBestMove() const
{
    return this->bestMove;
}
