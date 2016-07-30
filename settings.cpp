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
