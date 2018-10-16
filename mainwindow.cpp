#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QRegExp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    system = new System;
    auto view = ui->graphicsView;
    view->setScene(system->scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonAccept_clicked()
{
    auto textEdit = ui->textEdit;
    QString request = textEdit->toPlainText();
    QRegExp regular("\\badd\\b x-?(\\d\\d?\\d?) y-?(\\d\\d?\\d?) m(\\d\\d\\d?\\d?)");
    if (regular.indexIn(request) != -1) {
        system->system.push_back(Planet(regular.cap(1).toInt(), regular.cap(2).toInt(),
                                        regular.cap(3).toInt(), 10));
        system->scene->addItem(system->system.back().planet);
    }
}
