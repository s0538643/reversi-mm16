#ifndef SPIELBRETT_H
#define SPIELBRETT_H

#include <list>


class Spielbrett
{

 public:

    enum Zellen_Farbe {
        LEER = 0,
        WEISS =1,
        SCHWARZ =2,
    };

    struct SpielPosition {
        int x;
        int y;
    };

    Spielbrett();
    void erzeugeBrett(int groesse, int style);
    void setGroesse(int a);
    int getGroesse();
    int getPosition(SpielPosition a);
    int getPosition(int x, int y);
    bool istZelleBelegt(SpielPosition position);
    Zellen_Farbe getGegnerFarbe(Zellen_Farbe spieler);
    bool Zug(SpielPosition position, Zellen_Farbe spieler, bool fuehreAus);
    Zellen_Farbe getFarbe(SpielPosition a);
    void setFarbe(SpielPosition a, Zellen_Farbe);
    int zaehleSteine(Zellen_Farbe farbe);
    int getBrettstyle();
    void setBrettstyle(int style);
    std::list<SpielPosition> getValideZuege(Zellen_Farbe spieler);

    Zellen_Farbe * farbe;

private:

    int groesse;
    int brettStyle;

};

#endif // SPIELBRETT_H
