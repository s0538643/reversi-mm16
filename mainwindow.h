#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settings.h"
#include "spielbrett.h"
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


private:


private slots:
    void on_settingsButton_clicked();

    void on_exitButton_clicked();

    void on_startButton_clicked();

private:
    Ui::MainWindow *ui;
    BrettWidget *brettwidget = new BrettWidget(this);
    Settings settings;


};

#endif // MAINWINDOW_H
