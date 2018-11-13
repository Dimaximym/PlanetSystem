#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "system.h"
#include "parser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    System *system;
    Parser *parser;

private slots:
    void on_buttonAccept_clicked();
public slots:
    void createBody(int x, int y, int mass, int rad);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
