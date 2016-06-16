#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <string>
#include <QSettings>
#include <QTranslator>
#include <QAbstractButton>

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

    int getStyle();

    int getFeldGroesse();



private slots:




   void on_horizontalSlider_sliderMoved(int position);

   void on_horizontalSlider_sliderReleased();

   void on_horizontalSlider_valueChanged(int value);

//Für Auswahl der Styles

   void on_savebuttonBox_clicked(QAbstractButton *button);

private:
   void writeSettings();
   void readSettings();
   void applySettings();
   GameSettings currentSettings;
    Ui::Settings *ui;
};

#endif // SETTINGS_H
