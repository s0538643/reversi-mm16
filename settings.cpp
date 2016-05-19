#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}


void Settings::on_horizontalSlider_sliderMoved(int position)
{
    this->ui->feldgroesse->setText(QString::number(position));
}

