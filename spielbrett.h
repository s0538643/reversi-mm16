#ifndef SPIELBRETT_H
#define SPIELBRETT_H


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
    void erzeugeBrett(int groesse);
    void setGroesse(int a);
    int getGroesse();
    int getPosition(SpielPosition a);
    int getPosition(int x, int y);

    Zellen_Farbe getFarbe(SpielPosition a);

    Zellen_Farbe * farbe;

private:

    //int SpielPosition[16][16];
    int groesse;

};

#endif // SPIELBRETT_H
