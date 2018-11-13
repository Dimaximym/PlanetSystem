#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QRegExp"
#include "parser.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    system = new System;
    auto view = ui->graphicsView;
    view->setScene(system->scene);

    view->centerOn(system->planetSystem[0].planet);

    parser = new Parser;
    connect(parser, SIGNAL(invokeCreateBody(int,int,int,int)),
            this, SLOT(createBody(int,int,int,int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonAccept_clicked()
{
    auto textEdit = ui->textEdit;
    QString request = textEdit->toPlainText();

    parser->Parsing(request);
//    QRegExp regular("\\badd\\b x-?(\\d\\d?\\d?) y-?(\\d\\d?\\d?) m(\\d\\d\\d?\\d?)");
//    if (regular.indexIn(request) != -1) {
//        system->system.push_back(Planet(regular.cap(1).toInt(), regular.cap(2).toInt(),
//                                        regular.cap(3).toInt(), 10));
//        system->scene->addItem(system->system.back().planet);
//    }
}

void MainWindow::createBody(int x, int y, int mass, int rad)
{
    system->planetSystem.push_back(Planet(x, y, mass, rad));
    system->scene->addItem(system->planetSystem.back().planet);
}
