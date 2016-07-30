#include "mainwindow.h"
#include "ui_mainwindow.h"
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


    if (spielwindow != NULL)
    {
          spielwindow->close();
          spielwindow->brettwidget->brett.setSpielerfarbe(Spielbrett::WEISS);
    }



    spielwindow->brettwidget->brett.erzeugeBrett(this->settings.getFeldGroesse(), this->settings.getStyle(), this->settings.getSchwierigkeit());
    spielwindow->brettwidget->brett.setBestMove({0,0});
    spielwindow->brettwidget->brett.setSpielEnde(false);

    spielwindow->resize(800, 800);
    spielwindow->show();




    QObject::connect(spielwindow->brettwidget, SIGNAL(brettVeraendert()), spielwindow, SLOT(updateLabels()));
    QObject::connect(&this->settings, SIGNAL(settingsUpdated(int)), spielwindow->brettwidget, SLOT(updatedStyle(int)));
    QObject::connect(spielwindow->brettwidget, SIGNAL(zelleGeklickt(Spielbrett::SpielPosition)), spielwindow->brettwidget, SLOT(handleZelleGeklickt(Spielbrett::SpielPosition)));
    QObject::connect(spielwindow->brettwidget, SIGNAL(zugAusgefuehrt()), spielwindow->brettwidget, SLOT(handleZugAusgefuehrt()));




}
