#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include "pressed.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void button_pressed();
public:
    explicit MainWindow(QWidget *parent = 0);
    pressed* square[9][9];
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_test_clicked();
    void generatenull();
    void newgame();
    void answer();
    void answernew();
    void hide();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
