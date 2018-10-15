#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    System *system = new System;
    auto view = ui->graphicsView;
    view->setScene(system->scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}
