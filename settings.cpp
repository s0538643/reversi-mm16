#include "settings.h"
#include "ui_settings.h"
#include <QSettings>
#include <QtWidgets/QAbstractButton>
#include <QDebug>

void Settings::on_horizontalSlider_sliderMoved(int position)
{
    this->ui->feldgroesse->setText(QString::number(position));


}

int Settings::getFeldGroesse()
{
    return this->ui->horizontalSlider->value();
}

int Settings::getSpielerfarbe()
{
    return this->ui->comboBox_2->currentIndex();
}


void Settings::on_horizontalSlider_2_valueChanged(int value)
{
    this->ui->schwierigkeit_2->setText(QString::number(value));
}

/** Settings Part für Styles und Language***/


/**
 * Constructor
 * Loads all settings from ini
 *
 * @param parent
 */
Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    Settings::readSettings();
}

/**
 * Destructor
 * Saves all settings to ini
 *
 */
Settings::~Settings()
{
    Settings::writeSettings();
    delete ui;
}

/**
 * Get the actual settings
 *
 * @return SettingsDialog::Settings
 */

Settings::GameSettings Settings::gamesettings() const
{
   return currentSettings;
}

/**
 * Write settings to ini file
 *
 */
void Settings::writeSettings()

{
    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.beginGroup("Settings");
    settings.setValue("layout", this->ui->comboBox->currentIndex());
    settings.endGroup();

}

/**
 * Read settings from ini file
 *
 */
void Settings::readSettings()
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.beginGroup("Settings");
    currentSettings.style = settings.value("layout").toInt();
    this->applySettings();
    settings.endGroup();
}

/**
 * Apply settings to ui elements
 *
 */
void Settings::applySettings()
{
    this->ui->comboBox->setCurrentIndex(currentSettings.style);
  //  this->ui->languageBox->setCurrentIndex(currentSettings.language);
}

/**
 * Get the actual style from ini
 *
 * @return int
 */
int Settings::getStyle()
{
    return this->ui->comboBox->currentIndex();
}




void Settings::on_comboBox_currentIndexChanged(int index)
{
    emit this->settingsUpdated(index);
}

int Settings::getSchwierigkeit()
{
    return this->ui->horizontalSlider_2->value();
}

QString Settings::getName1()
{
    return this->ui->lineEdit->text();
}

QString Settings::getName2()
{
    return this->ui->lineEdit_2->text();
}

void Settings::sprache(int sprache)
{
    if (sprache == 0)
    {
        this->ui->brettgroesse->setText("Brettgroesse");
        this->ui->lineEdit->setText("Weiss");
        this->ui->lineEdit_2->setText("Schwarz");
        this->ui->brettstyle->setText("Brettstyle");
        this->ui->comboBox_2->setItemText(0, "Weiss");
        this->ui->comboBox_2->setItemText(1, "Schwarz");
        this->ui->label_2->setText("Spielernamen");
        this->ui->label->setText("Beginnender Spieler");
        this->ui->schwierigkeit_beschr->setText("KI Schwierigkeit \n(0 deaktiviert die KI");
    }
    else if (sprache == 1)
    {
        this->ui->brettgroesse->setText("Board size");
        this->ui->lineEdit->setText("White");
        this->ui->lineEdit_2->setText("Black");
        this->ui->brettstyle->setText("Board style");
        this->ui->comboBox_2->setItemText(0, "White");
        this->ui->comboBox_2->setItemText(1, "Black");
        this->ui->label_2->setText("Player names");
        this->ui->label->setText("Beginning player");
        this->ui->schwierigkeit_beschr->setText("AI difficulty \n(0 deactivates the AI");
    }
}
