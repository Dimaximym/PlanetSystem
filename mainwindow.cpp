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

    parser = new Parser();
    connect(parser, SIGNAL(invokeCreateBody(int,int,int,int)),
            this, SLOT(createBody(int,int,int,int)));
    connect(parser, SIGNAL(invokeFillLog(QString,QString,QString)),
            this, SLOT(FillLog(QString,QString,QString)));
    connect(parser, SIGNAL(invokeClear()),
            this, SLOT(clear()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonAccept_clicked()
{
    ui->errorLog->clear();
    QString request = ui->inputEdit->toPlainText();

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
    qDebug() << "Body was created.";
    system->planetSystem.push_back(Planet(x, y, mass, rad));
    system->scene->addItem(system->planetSystem.back().planet);
}

void MainWindow::FillLog(QString err, QString src, QString rx)
{
    ui->errorLog->clear();
    QRegExp erx(rx);
    erx.indexIn(src);
    qDebug() << "ERROR: " << err + " Слово: " + erx.cap(1);
    ui->errorLog->setText(err + " Слово: " + erx.cap(1));

    // Выделение в input edit
//    int index = ui->inputEdit->toPlainText().indexOf(erx.cap(1));
//    int endIndex = index + erx.cap(0).size();
//    qDebug() << erx.cap(0).size() << erx.cap(1).size();

//    QTextCursor cursor=ui->inputEdit->textCursor();
//    cursor.setPosition(0);
//    cursor.setPosition(ui->inputEdit->toPlainText().size(),QTextCursor::KeepAnchor);
//    QTextCharFormat charFormat = cursor.charFormat();
//    charFormat.clearBackground();
//    cursor.setCharFormat(charFormat);
//    ui->inputEdit->setTextCursor(cursor);

//    cursor=ui->inputEdit->textCursor();
//    cursor.setPosition(index);
//    cursor.setPosition(endIndex,QTextCursor::KeepAnchor);
//    charFormat = cursor.charFormat();
//    charFormat.setBackground(Qt::red);
//    cursor.setCharFormat(charFormat);
//    ui->inputEdit->setTextCursor(cursor);

    // Выделение в error log
//    int index = ui->errorLog->toPlainText().size() + QString("\n\nСтрока:\n").size() + src.indexOf(erx.cap(1));
//    int endIndex = index + erx.cap(0).size();
//    qDebug() << erx.cap(0).size() << erx.cap(1).size();

//    ui->errorLog->setText(ui->errorLog->toPlainText() + "\n\nСтрока:\n" + src);

//    QTextCursor cursor=ui->errorLog->textCursor();
//    cursor.setPosition(0);
//    cursor.setPosition(ui->errorLog->toPlainText().size(),QTextCursor::KeepAnchor);
//    QTextCharFormat charFormat = cursor.charFormat();
//    charFormat.clearBackground();
//    cursor.setCharFormat(charFormat);
//    ui->errorLog->setTextCursor(cursor);

//    cursor=ui->errorLog->textCursor();
//    cursor.setPosition(index);
//    cursor.setPosition(endIndex,QTextCursor::KeepAnchor);
//    charFormat = cursor.charFormat();
//    charFormat.setBackground(Qt::red);
//    cursor.setCharFormat(charFormat);
//    ui->errorLog->setTextCursor(cursor);

//    ui->errorLog->setFocus();
}

void MainWindow::clear()
{
    // Очистка системы тел
    //system->scene->clear();
    //system->planetSystem.clear();
    auto view = ui->graphicsView;
    view->setScene(nullptr);




    delete system;
    system = new System;
    view->setScene(system->scene);
    view->centerOn(system->planetSystem[0].planet);

//    int i = 0;
//    while(system->planetSystem.size() >= 0)
//    {
//        system->scene->removeItem(system->planetSystem.at(i).planet);
//        system->planetSystem.remove(i);
//        ++i;
//    }
}
