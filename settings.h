#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtWidgets/QDialog>
#include <string>
#include <QSettings>
#include <QTranslator>
#include <QtWidgets/QAbstractButton>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:




    struct GameSettings {
        int style;
      //  int language;
    };

    explicit Settings(QWidget *parent = 0);
    ~Settings();
    GameSettings gamesettings()const;

    /** Liefert den Style, der im Optionsmenu ausgewehlt ist.
     * @brief getStyle
     * @return Der gewaehlte Style als integer.
     */
    int getStyle();

    /** Liefert die Feldgroesse, die im Optionsmenu ausgewaehlt ist.
     * @brief getFeldGroesse
     * @return Die Feldgroesse als integer
     */
    int getFeldGroesse();

    int getSpielerfarbe();

    /** Liefert die im Optionsmenu festgelegte Schwierigkeit der KI.
     * @brief getSchwierigkeit
     * @return Die Schwierigkeit des KI Gegners.
     */
    int getSchwierigkeit();
    /** Liefert den Namen des weissen Spielers
     * @brief getName1
     * @return Der Name des weissen Spielers.
     */
    QString getName1();
    /** Liefert den Namen des schwarzen Spielers
     * @brief getName2
     * @return Der Name des schwarzen Spielers.
     */
    QString getName2();
    /** Aendert die Beschriftung des Optionsmenues abhaengig von der gewaehlten Sprache.
     * @brief sprache
     * @param sprache die gewaehlte sprache
     */
    void sprache(int sprache);
signals:
    /** Signalisiert dass die Styleoptionen aktualisiert wurden
     * @brief settingsUpdated
     * @param style Der gewaehlte style.
     */
    void settingsUpdated(int style);

private slots:
    /** Setzt den zum Feldgroessen Slider gehoerigen Text auf den aktuellen Wert des Sliders.
    * @brief on_horizontalSlider_sliderMoved
    * @param position Der Wert des Sliders.
    */
   void on_horizontalSlider_sliderMoved(int position);

   /** Setzt den zum Schwierigkeits Slider gehoerigen Text auf den aktuellen Wert des Sliders.
   * @brief on_horizontalSlider_2_valueChanged
   * @param value Der Wert des Sliders.
   */
   void on_horizontalSlider_2_valueChanged(int value);

//Für Auswahl der Styles

   /** Emitiert Signal wenn Style gewechselt wird.
    * @brief on_comboBox_currentIndexChanged
    * @param index Der Style als integer.
    */
   void on_comboBox_currentIndexChanged(int index);



private:
    void writeSettings();
    void readSettings();
    void applySettings();
    GameSettings currentSettings;
    Ui::Settings *ui;
};

#endif // SETTINGS_H
