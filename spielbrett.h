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

    Spielbrett(const Spielbrett& spielbrett);

    /** Erzeugt das Spielfeld, wie es zu Beginn einer Partie ist.
     * @brief erzeugeBrett
     * @param groesse Die Feldgroesse des Spielfeldes
     * @param style Der Style der Spielsteine.
     * @param schwierigkeit Die Schwierigkeit des KI Gegners.
     * @param spielerfarbe Die Spielerfarbe des Spielers, der am Zug ist.
     */
    void erzeugeBrett(int groesse, int style, int schwierigkeit, Zellen_Farbe spielerfarbe);

    /** Legt die Groesse des Spielfeldes fest.
     * @brief setGroesse
     * @param a Die Groesse des Spielfeldes.
     */
    void setGroesse(int a);

    /** Liefert die Groesse des Spielfeldes.
     * @brief getGroesse
     * @return Die Groesse des Spielfeldes.
     */
    int getGroesse();

    /** Liefert den zugehoerigen Index fuer die Zelle des Spielfelds.
     * @brief getPosition
     * @param a Die Zelle des Spielfelds.
     * @return Den Index.
     */
    int getPosition(SpielPosition a);
    /** Liefert den zugehoerigen Index fuer die Zelle des Spielfelds.
     * @brief getPosition
     * @param x Die x-Koordinate der Zelle.
     * @param y Die y-Koordinate der Zelle.
     * @return Den Index.
     */
    int getPosition(int x, int y);
    /** Prueft ob eine Zelle bereits belegt ist.
     * @brief istZelleBelegt
     * @param position Die Zelle die geprueft wird.
     * @return True, wenn die Zelle bereits belegt ist.
     */
    bool istZelleBelegt(SpielPosition position);
    /** Liefert die jeweils entgegengesetzte Farbe (Schwarz<->Weiss)
     * @brief getGegnerFarbe
     * @param spieler Die Farbe deren Gegensatz gesucht wird.
     * @return Die entgegengesetzte Farbe.
     */
    Zellen_Farbe getGegnerFarbe(Zellen_Farbe spieler);
    /** Prueft ob ein Zug an der Position moeglich ist und fuehrt ihn aus, wenn gewollt.
     * @brief Zug
     * @param position Position an der der Zug geprueft werden soll.
     * @param spieler Die Farbe des Spielers fuer den der Zug ausgefuehrt werden soll.
     * @param fuehreAus Wenn True wird der Zug auch ausgefuehrt.
     * @return True wenn der Zug moeglich ist.
     */
    bool Zug(SpielPosition position, Zellen_Farbe spieler, bool fuehreAus);
    /** Liefert die Farbe einer Zelle.
     * @brief getFarbe
     * @param a Die Position der Zelle.
     * @return Die Farbe der Zelle.
     */
    Zellen_Farbe getFarbe(SpielPosition a);
    /** Legt die Farbe einer Zelle fest.
     * @brief setFarbe
     * @param a Die Position der Zelle.
     * @param farbe Die Farbe, auf die die Zelle festgelegt werden soll.
     */
    void setFarbe(SpielPosition a, Zellen_Farbe farbe);
    /** Gibt die totale Anzahl an Steinen der Farbe auf dem Spielfeld aus.
     * @brief zaehleSteine
     * @param farbe Die Farbe deren Steine gezaehlt werden sollen.
     * @return Die Anzahl der Steine.
     */
    int zaehleSteine(Zellen_Farbe farbe);
    /** Liefert den Style des Spielfelds.
     * @brief getBrettstyle
     * @return Der Style des Spielfelds.
     */
    int getBrettstyle();
    /** Legt den Style des Spielfelds fest.
     * @brief setBrettstyle
     * @param style Der Style des Spielfelds.
     */
    void setBrettstyle(int style);
    /** Liefert alle moeglichen Zuege fuer eine Farbe zurueck.
     * @brief getValideZuege
     * @param spieler Die Farbe deren gueltige Zuege gesucht werden.
     * @return Eine Liste die alle gueltigen Zuege enthaelt.
     */
    std::list<SpielPosition> getValideZuege(Zellen_Farbe spieler);
    /** Legt fest ob das Spiel vorbei ist.
     * @brief setSpielEnde
     * @param ende Wenn True, ist das Spiel zu Ende.
     */
    void setSpielEnde(bool ende);
    /** Liefert ob das Spiel vorbei ist.
     * @brief getSpielEnde
     * @return True, wenn das Spiel vorbei ist.
     */
    bool getSpielEnde();
    /** Liefert den Sieger des Spiels.
     * @brief getSieger
     * @return Die Farbe des Siegers. Oder LEER bei einem Unentschieden.
     */
    Zellen_Farbe getSieger();

    /** Liefert die Spielerfarbe.
     * @brief getSpielerFarbe
     * @return Die Spielerfarbe.
     */
    Zellen_Farbe getSpielerFarbe();
    /** Legt die Spielerfarbe fest.
     * @brief setSpielerfarbe
     * @param f Die Spielerfarbe.
     */
    void setSpielerfarbe(Zellen_Farbe f);
    /** Liefert den guenstigsten Zug.
     * @brief getBestMove
     * @return Der guenstigste Zug.
     */
    SpielPosition getBestMove();
    /** Legt den guenstigsten Zug fest.
     * @brief setBestMove
     * @param a Der Zug.
     */
    void setBestMove(SpielPosition a);
    /** Berechnet den guenstigsten Zug.
     * @brief calculateBestMove
     * @param player Die Farbe des Spielers fuer den der guenstigste Zug berechnet werden soll.
     * @param difficulty Die Schwierigkeitsstufe der KI.
     */
    void calculateBestMove(Zellen_Farbe player,int difficulty);
    /** Legt die Schwierigkeitsstufe der KI fest.
     * @brief setSchwierigkeit
     * @param schwierigkeit Die Schwierigkeitsstufe.
     */
    void setSchwierigkeit(int schwierigkeit);
    /** Liefert die Schwierigkeitsstufe der KI.
     * @brief getSchwierigkeit
     * @return Die Schwierigkeitsstufe.
     */
    int getSchwierigkeit();

    Zellen_Farbe * farbe;

private:

    //initialisieren der Membervariablen!

    int groesse ;
    int brettStyle ;
    int schwierigkeit ;
    bool spielEnde ;
    Zellen_Farbe Spielerfarbe ;

    SpielPosition bestMove;


};

#endif // SPIELBRETT_H
