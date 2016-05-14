#include "spielbrett.h"


Spielbrett::Spielbrett()
{
    this->groesse = 8;
}


void Spielbrett::erzeugeBrett(int groesse)
{
    this->setGroesse(groesse);
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
