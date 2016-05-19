#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <string>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();


private slots:


   void on_horizontalSlider_sliderMoved(int position);

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
