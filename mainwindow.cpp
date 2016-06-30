#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings.h"
#include "spielbrett.h"
#include "brettwidget.h"
#include "spielwindow.h"
#include <QPainter>
#include <QMediaPlayer>
#include <QSound>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_settingsButton_clicked()
{
    //Settings settings;
    this->settings.setModal(true);
    this->settings.exec();

}

void MainWindow::on_exitButton_clicked()
{
    this->close();
}

void MainWindow::on_startButton_clicked()
{
    //play Backround Music/ start sound
    QMediaPlayer * start = new QMediaPlayer();
    start ->setMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/audio/Barbarian-Chant.wav"));
      start ->play();

    SpielWindow *spielwindow = new SpielWindow();
    spielwindow->brettwidget->brett.erzeugeBrett(this->settings.getFeldGroesse(), this->settings.getStyle());
    spielwindow->resize(800, 800);
    spielwindow->show();

    /*if (brettwidget != NULL)
        brettwidget->close();
    brettwidget->brett.erzeugeBrett(this->settings.getFeldGroesse(), this->settings.getStyle());
    brettwidget->resize(500, 500);
    brettwidget->show();*/



}
