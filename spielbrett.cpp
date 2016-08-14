#include "spielbrett.h"
#include <QDebug>
#include "minimax.h"

Spielbrett::Spielbrett()
{
    this->groesse = 8;
    this->spielEnde = false;
}


void Spielbrett::erzeugeBrett(int groesse, int style, int schwierigkeit, Zellen_Farbe spielerfarbe)
{

    this->setSpielEnde(false);
    this->setGroesse(groesse);
    this->setBrettstyle(style);
    this->setSchwierigkeit(schwierigkeit);
    this->setSpielerfarbe(spielerfarbe);
    this->farbe = new Zellen_Farbe[this->getGroesse()*this->getGroesse()];
    SpielPosition position;
    for (int i=0; i<groesse; i++)
    {
      for (int j=0; j<groesse; j++)
      {
          position = {i,j};
          this->farbe[this->getPosition(position)] = LEER;
      }
    }
        position = {groesse/2,groesse/2};
        this->farbe[this->getPosition(position)] = SCHWARZ;

        position = {(groesse/2),(groesse/2-1)};
        this->farbe[this->getPosition(position)] = WEISS;


        position = {(groesse/2)-1,(groesse/2)};
        this->farbe[this->getPosition(position)] = WEISS;


         position = {(groesse/2)-1,(groesse/2)-1};
         this->farbe[this->getPosition(position)] = SCHWARZ;

}

void Spielbrett::setGroesse(int groesse)
{
    this->groesse = groesse;
}

int Spielbrett::getGroesse()
{
    return this->groesse;
}

int Spielbrett::getPosition(SpielPosition a)
{
    return a.y*this->getGroesse()+a.x;
}

int Spielbrett::getPosition(int x, int y)
{
    return y*this->getGroesse() + x;
}

Spielbrett::Zellen_Farbe Spielbrett::getFarbe(SpielPosition a)
{
    return this->farbe[this->getPosition(a)];
}

void Spielbrett::setFarbe(SpielPosition position, Zellen_Farbe spielfarbe)
{
    this->farbe[this->getPosition(position)] = spielfarbe;
}

bool Spielbrett::istZelleBelegt(SpielPosition position)
{
    return (this->getFarbe(position) != LEER);
}

Spielbrett::Zellen_Farbe Spielbrett::getGegnerFarbe(Zellen_Farbe spieler)
{
    if (spieler == WEISS)
        return SCHWARZ;
    else if (spieler == SCHWARZ)
        return WEISS;
    else
        return LEER;

}

bool Spielbrett::Zug(SpielPosition position, Zellen_Farbe spieler, bool fuehreAus)
{
    if (this->istZelleBelegt(position)) {
        return false;
    }

    Zellen_Farbe gegner = this->getGegnerFarbe(spieler);

    bool zulaessig = false;

    //pruefe nach links
    {
        bool hatGegner = false;
        for (int x = position.x-1; x >= 0; x--)
        {
            SpielPosition platzhalter = {x,position.y};
            Zellen_Farbe platzhalterFarbe = this->getFarbe(platzhalter);
            //leere Zelle
            if (platzhalterFarbe == LEER)
                break;
            //Gegner Zelle
            else if (platzhalterFarbe == gegner)
                hatGegner = true;
            //Found friendly cell
            else if (platzhalterFarbe == spieler)
            {
                if (hatGegner)
                {
                    zulaessig = true;
                    if (fuehreAus)
                    {
                        for (int x2 = position.x; x2 >= platzhalter.x; x2--)
                        {
                            SpielPosition temp = {x2, position.y};
                            this->setFarbe(temp, spieler);
                        }
                    }
                }
                break;
            }
        }
    }

    //pruefe nach rechts
    {
        bool hatGegner = false;
        for (int x = position.x+1; x < this->getGroesse(); x++)
        {
            SpielPosition platzhalter = {x,position.y};
            Zellen_Farbe platzhalterFarbe = this->getFarbe(platzhalter);
            if (platzhalterFarbe == LEER)
                break;
            else if (platzhalterFarbe == gegner)
                hatGegner = true;
            else if (platzhalterFarbe == spieler)
            {
                if (hatGegner)
                {
                    zulaessig = true;
                    if (fuehreAus)
                    {
                    for (int x2 = position.x; x2 <= platzhalter.x; x2++)
                    {
                        SpielPosition temp = {x2, position.y};
                        this->setFarbe(temp, spieler);
                    }
                    }
                }
                break;
            }
        }
    }

    //pruefe nach oben
    {
        bool hatGegner = false;
        for (int y = position.y+1; y < this->getGroesse(); y++)
        {
            SpielPosition platzhalter = {position.x,y};
            Zellen_Farbe platzhalterFarbe = this->getFarbe(platzhalter);
            if (platzhalterFarbe == LEER)
                break;
            else if (platzhalterFarbe == gegner)
                hatGegner = true;
            else if (platzhalterFarbe == spieler)
            {
                if (hatGegner)
                {
                    zulaessig = true;
                    if (fuehreAus)
                    {
                    for (int y2 = position.y; y2 <= platzhalter.y; y2++)
                    {
                        SpielPosition temp = {position.x, y2};
                        this->setFarbe(temp, spieler);
                    }
                    }
                }
                break;
            }
        }
    }

    //pruefe nach unten
    {
        bool hatGegner = false;
        for (int y = position.y-1; y >= 0; y--)
        {
            SpielPosition platzhalter = {position.x,y};
            Zellen_Farbe platzhalterFarbe = this->getFarbe(platzhalter);
            if (platzhalterFarbe == LEER)
                break;
            else if (platzhalterFarbe == gegner)
                hatGegner = true;
            else if (platzhalterFarbe == spieler)
            {
                if (hatGegner)
                {
                    zulaessig = true;
                    if (fuehreAus)
                    {
                    for (int y2 = position.y; y2 >= platzhalter.y; y2--)
                    {
                        SpielPosition temp = {position.x, y2};
                        this->setFarbe(temp, spieler);
                    }
                    }
                }
                break;
            }
        }
    }

    //pruefe diagonal oben rechts
    {
        bool hatGegner = false;
        int x = position.x+1;
        int y = position.y+1;
        while (x < this->getGroesse() && y < this->getGroesse())
        {
            SpielPosition platzhalter = {x,y};
            Zellen_Farbe platzhalterFarbe = this->getFarbe(platzhalter);
            if (platzhalterFarbe == LEER)
                break;
            else if (platzhalterFarbe == gegner)
                hatGegner = true;
            else if (platzhalterFarbe == spieler)
            {
                if (hatGegner)
                {
                    zulaessig = true;
                    if (fuehreAus)
                    {
                    int x2 = position.x;
                    int y2 = position.y;
                    while (x2 <= platzhalter.x && y2 <= platzhalter.y)
                    {

                                SpielPosition temp = {x2, y2};
                                this->setFarbe(temp, spieler);
                                x2++;
                                y2++;


                    }
                    }

                }
                break;
            }
            x++;
            y++;
        }
    }

    //pruefe diagonal oben links
    {
        bool hatGegner = false;
        int x = position.x-1;
        int y = position.y+1;
        while (x >= 0 && y < this->getGroesse())
        {
            SpielPosition platzhalter = {x,y};
            Zellen_Farbe platzhalterFarbe = this->getFarbe(platzhalter);
            if (platzhalterFarbe == LEER)
                break;
            else if (platzhalterFarbe == gegner)
                hatGegner = true;
            else if (platzhalterFarbe == spieler)
            {
                if (hatGegner)
                {
                    zulaessig = true;
                    if (fuehreAus)
                    {
                    int x2 = position.x;
                    int y2 = position.y;
                    while (x2 >= platzhalter.x && y2 <= platzhalter.y)
                    {

                                SpielPosition temp = {x2, y2};
                                this->setFarbe(temp, spieler);
                                x2--;
                                y2++;


                    }
                    }

                }
                break;
            }
            x--;
            y++;
        }
    }

    //prüfe diagonal rechts unten
    {
        bool hatGegner = false;
        int x = position.x+1;
        int y = position.y-1;
        while (x < this->getGroesse()&& y >= 0)
        {
            SpielPosition platzhalter = {x,y};
            Zellen_Farbe platzhalterFarbe = this->getFarbe(platzhalter);
            if (platzhalterFarbe == LEER)
                break;
            else if (platzhalterFarbe == gegner)
                hatGegner = true;
            else if (platzhalterFarbe == spieler)
            {
                if (hatGegner)
                {
                    zulaessig = true;
                    if (fuehreAus)
                    {
                    int x2 = position.x;
                    int y2 = position.y;
                    while (x2 <= platzhalter.x && y2 >= platzhalter.y)
                    {

                                SpielPosition temp = {x2, y2};
                                this->setFarbe(temp, spieler);
                                x2++;
                                y2--;


                    }
                    }

                }
                break;
            }
            x++;
            y--;
        }
    }

    //pruefe diagonal unten links
    {
        bool hatGegner = false;
        int x = position.x-1;
        int y = position.y-1;
        while (x >= 0 && y >= 0)
        {
            SpielPosition platzhalter = {x,y};
            Zellen_Farbe platzhalterFarbe = this->getFarbe(platzhalter);
            if (platzhalterFarbe == LEER)
                break;
            else if (platzhalterFarbe == gegner)
                hatGegner = true;
            else if (platzhalterFarbe == spieler)
            {
                if (hatGegner)
                {
                    zulaessig = true;
                    if (fuehreAus)
                    {
                    int x2 = position.x;
                    int y2 = position.y;
                    while (x2 >= platzhalter.x && y2 >= platzhalter.y)
                    {

                                SpielPosition temp = {x2, y2};
                                this->setFarbe(temp, spieler);
                                x2--;
                                y2--;


                    }
                    }
                }
                break;
            }
            x--;
            y--;
        }
    }
    return zulaessig;
}

int Spielbrett::zaehleSteine(Zellen_Farbe farbe)
{
    int anzahl = 0;
    SpielPosition pos;
    for (int x=0; x<this->getGroesse(); x++)
        for (int y=0; y<this->getGroesse(); y++)
        {
            pos = {x,y};
            if (this->getFarbe(pos) == farbe)
            anzahl += 1;
         }
    return anzahl;
}

/**
 * Get brett style (0=Default, 1=Alternativ, 2=Viking)
 *
 * @return int
 */
int Spielbrett::getBrettstyle()
{
    return this->brettStyle;
}

void Spielbrett::setBrettstyle(int style)
{
    this->brettStyle = style;
}

std::list<Spielbrett::SpielPosition> Spielbrett::getValideZuege(Zellen_Farbe spieler)
{
    std::list<SpielPosition> valideZuege = {};
    for (int x = 0; x < this->getGroesse(); x++)
    {
        for (int y = 0; y < this->getGroesse(); y++)
        {
            SpielPosition position = {x, y};
            if (this->Zug(position, spieler, false))
                valideZuege.push_back(position);

        }
    }
    return valideZuege;
}

void Spielbrett::setSpielEnde(bool ende)
{
    this->spielEnde = ende;
}

bool Spielbrett::getSpielEnde()
{
    return this->spielEnde;
}

Spielbrett::Zellen_Farbe Spielbrett::getSieger()
{
    if (this->zaehleSteine(SCHWARZ) > this->zaehleSteine(WEISS))
        return SCHWARZ;
    else if (this->zaehleSteine(WEISS) > this->zaehleSteine(SCHWARZ))
        return WEISS;
    else
        return LEER;
}



Spielbrett::Zellen_Farbe Spielbrett::getSpielerFarbe()
{
    return this->Spielerfarbe;
}

void Spielbrett::setSpielerfarbe(Spielbrett::Zellen_Farbe farbe)
{
    this->Spielerfarbe = farbe;
}

Spielbrett::SpielPosition Spielbrett::getBestMove()
{
    return this->bestMove;
}

void Spielbrett::setBestMove(Spielbrett::SpielPosition a)
{
    this->bestMove = a;
}

void Spielbrett::calculateBestMove(Zellen_Farbe player,int difficulty)
{
    player;
    Spielbrett board;
    board = *this;
    Minimax minimax(board, difficulty);
    minimax.search();
    this->bestMove = minimax.getBestMove();
}

void Spielbrett::setSchwierigkeit(int schwierigkeit)
{
    this->schwierigkeit = schwierigkeit;
}

int Spielbrett::getSchwierigkeit()
{
    return this->schwierigkeit;
}
