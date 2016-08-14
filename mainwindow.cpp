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
    spielwindow  = new SpielWindow();
    sprache = 0;
    start = new QMediaPlayer();
}

MainWindow::~MainWindow()
{
    delete ui;
    if (spielwindow != NULL)
        delete spielwindow;
    delete start;
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
    this->spielwindow->close();
}

void MainWindow::on_startButton_clicked()
{
    //play Backround Music/ start sound


    start->stop();
    start ->setMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/audio/Barbarian-Chant.wav"));
      start ->play();

    spielwindow->close();

    Spielbrett::Zellen_Farbe spielerfarbe;
    if (this->settings.getSpielerfarbe() == 0)
        spielerfarbe = Spielbrett::WEISS;
    else
        spielerfarbe = Spielbrett::SCHWARZ;
    spielwindow  = new SpielWindow(this->settings.getName1(), this->settings.getName2(), spielerfarbe, this->getSprache());

    spielwindow->brettwidget->brett.erzeugeBrett(this->settings.getFeldGroesse(), this->settings.getStyle(), this->settings.getSchwierigkeit(), spielerfarbe);
    spielwindow->brettwidget->brett.setBestMove({0,0});
    spielwindow->brettwidget->brett.setSpielEnde(false);


    spielwindow->resize(800, 800);
    spielwindow->show();




    QObject::connect(spielwindow->brettwidget, SIGNAL(brettVeraendert()), spielwindow, SLOT(updateLabels()));
    QObject::connect(&this->settings, SIGNAL(settingsUpdated(int)), spielwindow->brettwidget, SLOT(updatedStyle(int)));
    QObject::connect(spielwindow->brettwidget, SIGNAL(zelleGeklickt(Spielbrett::SpielPosition)), spielwindow->brettwidget, SLOT(handleZelleGeklickt(Spielbrett::SpielPosition)));
    QObject::connect(spielwindow->brettwidget, SIGNAL(zugAusgefuehrt()), spielwindow->brettwidget, SLOT(handleZugAusgefuehrt()));
    QObject::connect(spielwindow->brettwidget, SIGNAL(checkPass(std::list<Spielbrett::SpielPosition>)), spielwindow->brettwidget, SLOT(handleCheckPass(std::list<Spielbrett::SpielPosition>)));




}

int MainWindow::getSprache()
{
    return this->sprache;

}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    this->sprache = index;

    if (index == 0)
    {
        this->ui->exitButton->setText("Beenden");
        this->ui->startButton->setText("Spiel starten");
        this->ui->settingsButton->setText("Spieleinstellungen");
    }
    if(index == 1)
    {
        this->ui->exitButton->setText("Exit");
        this->ui->startButton->setText("Game start");
        this->ui->settingsButton->setText("Settings");
    }

    this->settings.sprache(index);
    this->update();
}
