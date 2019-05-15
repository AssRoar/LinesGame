#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <ballbutton.h>
#include <QPainter>
#include <QPicture>
#include <QtDebug>
#include <QLabel>
#include <iostream>
#include <QPushButton>
#include <ctime>
#include <vector>
#include <QFile>
#include <string>
#include <fstream>
#include <QPropertyAnimation>
#include <QTimer>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTimer *tmr = new QTimer;
    BallButton* pole[9][9];
    int BallCount;
    QHBoxLayout * H;
    QVBoxLayout * V;
    QGridLayout * D;
    QVBoxLayout * VP;
    QPushButton *retry_B;
    QLabel *Ulbl = new QLabel;
    QLabel *REC = new QLabel;
    QLabel *Dlbl = new QLabel;
    QLabel *UREC = new QLabel;
    QLabel *wasted = new QLabel;
    int RECORD=0;
    int RESULT=0;
    int x;
    int y;
    bool N = false;
    bool WAY = false;
    int del(int x, int y);
    int paw(int k);
    std::vector <std::pair <int, int> > way(int x, int y, int tx, int ty);
public slots:
    void ifclicked();
    void retry();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
