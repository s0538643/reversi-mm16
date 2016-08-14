#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "settings.h"
#include "spielbrett.h"
#include "spielwindow.h"
#include "brettwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    /** Liefert die gewaehlte Sprache als Integerwert.
     * @brief getSprache
     * @return Die gewaehlte Sprache
     */
    int getSprache();




private slots:
    /** Wenn auf den Knopf "Spieleinstellungen" geklickt wird, öffnet sich das Optionsmenu.
     * @brief on_settingsButton_clicked
     */
    void on_settingsButton_clicked();

    /** Klicken auf den "Beenden" Knopf schliesst das Programm.
     * @brief on_exitButton_clicked
     */
    void on_exitButton_clicked();
    /** Klicken auf den "Spiel Starten" Button oeffnet das eigentliche Spielfeld in einem neuen Fenster
     * @brief on_startButton_clicked
     */
    void on_startButton_clicked();
    /** Slot fuer das aendern der Sprache.
     * @brief on_comboBox_currentIndexChanged
     * @param index
     */
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    BrettWidget *brettwidget  = new BrettWidget(this);
    SpielWindow *spielwindow;
    Settings settings;
    int sprache;
    QMediaPlayer * start;


};

#endif // MAINWINDOW_H
