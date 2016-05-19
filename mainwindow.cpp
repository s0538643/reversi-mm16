#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings.h"
#include "spielbrett.h"
#include "brettwidget.h"
#include <QPainter>

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

void MainWindow::on_pushButton_3_clicked()
{
    Settings settings;
    settings.setModal(true);
    settings.exec();

}

void MainWindow::on_pushButton_2_clicked()
{
    this->close();
}

void MainWindow::on_pushButton_clicked()
{
    BrettWidget *brettwidget = new BrettWidget(this);

    brettwidget->brett.erzeugeBrett(8);
    brettwidget->resize(500, 500);
    brettwidget->show();
    //brettwidget->activateWindow();
}
