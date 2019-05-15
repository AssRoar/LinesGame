#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>





void MainWindow::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    int penSize=1;

    //КРАСНЫЕ ЛИНИИ
//____________________________________________________
    QPen myPen(Qt::red, penSize, Qt::SolidLine);
    painter.setPen(myPen);
//    for (int i=1;i<=40;i++)
//    painter.drawLine(0, 20*i-7, 1200, 20*i-7);
//    for (int i=1;i<=60;i++)
//        painter.drawLine(20*i, 0, 20*i, 800);

    //БЕЛЫЕ ЛИНИИ
//____________________________________________________
    QPen mine(Qt::darkGray, 2, Qt::SolidLine);
    painter.setPen(mine);
    for (int i=0;i<=9;i++)
    painter.drawLine(23, 80*i+30, 743, 80*i+30);
    for (int i=0;i<=9;i++)
        painter.drawLine(80*i+23, 30, 80*i+23, 750);

    //БЕЛЫЕ КВАДРАТИКИ И ПРЯМОУГОЛЬНИК
//____________________________________________________
//    painter.drawRect(780, 33, 380,  140);
//    painter.drawRect(800, 53, 100,  100);
//    painter.drawRect(920, 53, 100,  100);
//    painter.drawRect(1040, 53, 100,  100);

}







    QFile file("/Users/asgor/Desktop/Progy/fileAS.txt");



    MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
    {
        ui->setupUi(this);

            //СОЗДАНИЕ
        //____________________________________________________
        H = new QHBoxLayout;
        V = new QVBoxLayout;
        D = new QGridLayout;
        VP = new QVBoxLayout;
        D->setVerticalSpacing(0);
        D->setHorizontalSpacing(0);

            //ВНЕСЕНИЕ КНОПОК
        //____________________________________________________
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                BallButton *pb=new BallButton;
//                pb->setStyleSheet("QPushButton { background: none; border: none; outline: none; color: transparent; } ");
                pb->setFixedHeight(93);
                pb->setFixedWidth(93);
                pb->i=i;
                pb->j=j;
                this->pole[i][j]=pb;
                connect(pb, SIGNAL(clicked()), this, SLOT(ifclicked()));
                D->addWidget(pb,i,j);
            }

        }


           //НАСТРОЙКА ПОЛОЖЕНИЯ
        //____________________________________________________
        {
            QPushButton *pb=new QPushButton;
          pb->setFixedHeight(25);
          pb->setFixedWidth(0);
          pb->setText("Undo");
          V->addLayout(D);
          V->addWidget(pb);
        }
        {
            retry_B=new QPushButton;
            QPushButton *AAHA = new QPushButton;
            AAHA->setFixedHeight(583);
            AAHA->setFixedWidth(0);
            VP->addWidget(AAHA);
            retry_B->setFixedHeight(93);
            retry_B->setFixedWidth(400);
            retry_B->setIcon(QIcon("/resource/images/Paz.gif"));
            retry_B->setText("Retry");
            VP->addWidget(retry_B);
            connect(retry_B, SIGNAL(clicked()), this, SLOT(retry()));

            H->addLayout(V);

            H->addLayout(VP);
            delete ui->centralWidget->layout();
            ui->centralWidget->setLayout(H);
        }

        //СОЗДАНИЕ ПЕРВЫХ 3Х КНОПОК
        //____________________________________________________
        for (int i=1;i<4;i++)
        {
            int sum=0;
            while (sum<1)
            {
                int k=rand()%9;
                int m=rand()%9;
                if (pole[k][m]->now_color==0)
                {
                    pole[k][m]->set_color(i);
                    sum++;
                }
            }
        }











        //НАСТРОЙКА РАСПОЛОЖЕНИЯ СЛОВ
        //____________________________________________________
        Ulbl = new QLabel(this);
        Ulbl->setGeometry(QRect(780, 43, 500, 150));
        QFont Uft = Ulbl -> font();
        Uft.setPixelSize(60);
        Ulbl->setFont(Uft);
        Ulbl->setText("Your score:\n");
        Ulbl->show();

        Dlbl = new QLabel(this);
        Dlbl->setGeometry(QRect(780, 103, 500, 100));
        QFont Dft = Dlbl -> font();
        Dft.setPixelSize(60);
        Dlbl->setFont(Dft);
        Dlbl->setText(QString::number(RECORD));
        Dlbl->show();

        UREC = new QLabel(this);
        UREC->setGeometry(QRect(780, 303, 500, 150));
        QFont URF = UREC -> font();
        URF.setPixelSize(60);
        UREC->setFont(URF);
        UREC->setText("Record:\n");
        UREC->show();

        REC = new QLabel(this);
        REC->setGeometry(QRect(780, 363, 500, 100));
        QFont DRF = REC -> font();
        DRF.setPixelSize(60);
        REC->setFont(DRF);
        REC->setText("0");
        REC->show();

        wasted = new QLabel(this);


        //ОТКРЫТИЕ ФАЙЛА ДЛЯ ЧТЕНИЯ И ВЫВОД
        if (file.open(QIODevice::ReadOnly))
        {
            QString str=file.read(8);
            RECORD=str.toInt();
        }
        file.close();
        REC->clear();
        REC->setText(QString::number(RECORD));
        REC->show();

    }








    MainWindow::~MainWindow()
    {
        delete ui;
    }








bool WAY=false;



void MainWindow::ifclicked()
{
    BallButton *bashka = (BallButton*)sender();
    if ((N)&&(bashka->i==x)&&(bashka->j==y))
    {
        N=false;

        return;
    }
    if ((!N)&&(bashka->now_color!=0))
    {
        x=bashka->i;
        y=bashka->j;
        N=true;

        return;
    }
    if ((N)&&(bashka->now_color!=0))
    {
        N=false;
        return;
    }
    if ((N)&&(bashka->now_color==0||bashka->now_color==4))
    {
//        path.resize(0);
        std::vector <std::pair <int, int>> path = way(x, y, bashka->i, bashka->j);

        if (!WAY)
        {
            N=false;
            qDebug() << "lol";
            return;
        }
        //ANIMATION@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        {
            int colorofbashka = pole[x][y]->now_color;
            QPropertyAnimation *animation1 = new QPropertyAnimation(pole[x][y], "iconSize");
            animation1->setDuration(20*(path.size()+1));
            animation1->setStartValue(pole[x][y]->iconSize());
            animation1->setEndValue(QSize(0, 0));
            animation1->start();
            while (animation1->state() != QAbstractAnimation::Stopped) QCoreApplication::processEvents();
            for (int i=1;i<path.size()-1;i++)
            {
                pole[path[i].first][path[i].second]->set_color(4);
                QPropertyAnimation *animation1 = new QPropertyAnimation(pole[path[i].first][path[i].second], "iconSize");
                animation1->setDuration(20);
                animation1->setStartValue(QSize(0, 0));
                animation1->setEndValue(pole[path[i].first][path[i].second]->iconSize());
                animation1->start();
                while (animation1->state() != QAbstractAnimation::Stopped) QCoreApplication::processEvents();
            }
            pole[x][y]->set_color(0);

            bashka->set_color(colorofbashka);

            for (int i=1;i<path.size()-1;i++)
            {
                QPropertyAnimation *animation1 = new QPropertyAnimation(pole[path[i].first][path[i].second], "iconSize");
                animation1->setDuration(20);
                animation1->setStartValue(pole[path[i].first][path[i].second]->iconSize());
                animation1->setEndValue(QSize(0, 0));
                animation1->start();
                while (animation1->state() != QAbstractAnimation::Stopped) QCoreApplication::processEvents();
                pole[path[i].first][path[i].second]->set_color(0);
            }
        }
//        pole[bashka->i][bashka->j]->set_color(pole[x][y]->now_color);
//        pole[x][y]->set_color(0);

        N=false;
        int s=0;
        for (int i=0;i<9;i++)
            for (int j=0;j<9;j++)
                if (pole[i][j]->now_color==4) pole[i][j]->set_color(0);
        for (int i=0;i<9;i++)
            for (int j=0;j<9;j++)
                if (pole[i][j]->now_color==0) s++;
        std::vector <std::pair < int , int > > pv (s);
        int qws=s;
        for (int i=0;i<9;i++)
            for (int j=0;j<9;j++)
                if (pole[i][j]->now_color==0)
                {
                    pv[--s].first=i; pv[s].second=j;
                }
        int nuj;
        if (qws>=3) nuj=3;
        else if (qws<3) nuj=qws;

        int schet=1;
        while (schet<=nuj)
        {
            int k=rand()%qws;
            if (pole[pv[k].first][pv[k].second]->now_color==0)
            {
                pole[pv[k].first][pv[k].second]->set_color(schet);
                int cnt=del(pv[k].first, pv[k].second);
                if (cnt)
                    RESULT+=paw(cnt);
                    Dlbl->clear();
                    Dlbl->setText(QString::number(RESULT));
                    Dlbl->show();
                if (RESULT>RECORD)
                {
                    RECORD=RESULT;
                    REC->clear();
                    REC->setText(QString::number(RECORD));
                    REC->show();

                    file.open(QIODevice::WriteOnly);
                    QTextStream stream( &file );
                    stream << RECORD << endl;
                    file.close();
                }
                schet++;

            }
        }

        int cnt = del(bashka->i, bashka->j);
        if (cnt)
        {
            RESULT+=paw(cnt);
            Dlbl->clear();
            Dlbl->setText(QString::number(RESULT));
            Dlbl->show();
            if (RESULT>RECORD)
            {
                RECORD=RESULT;
                REC->clear();
                REC->setText(QString::number(RECORD));
                REC->show();

                file.open(QIODevice::WriteOnly);
                QTextStream stream( &file );
                stream << RECORD << endl;
                file.close();

            }
        }
        int uuu=0;
        for (int i=0;i<9;i++)
            for (int j=0;j<9;j++)
                if (pole[i][j]->now_color==0) uuu++;
        if (!uuu)
        {
            wasted->setGeometry(QRect(0, 310, 1180, 160));
            QFont W = wasted -> font();
            W.setPixelSize(203);
            wasted->setFont(W);
            wasted->setStyleSheet("QLabel { background-color : RGBA(0, 0, 0, 0); color : red; }");
            wasted->setText("ПОТРАЧЕНО");
//            wasted->show();
//            wasted->setGeometry(QRect(0, 310, 0, 0));
        }
        return;
    }
}









void MainWindow::retry()
{
    for (int i=0;i<9;i++)
        for (int j=0;j<9;j++)
            pole[i][j]->set_color(0);
    RESULT=0;
    Dlbl->clear();
    Dlbl->setText(QString::number(RESULT));
    Dlbl->show();
    for (int i=1;i<4;i++)
    {
        int sum=0;
        while (sum<1)
        {
            int k=rand()%9;
            int m=rand()%9;
            if (pole[k][m]->now_color==0)
            {
                pole[k][m]->set_color(i);
                sum++;
            }
        }
    }
    N=false;
    wasted->setGeometry(QRect(0, 310, 0, 0));
    QString st=(wasted->text());
    if (st!="")
    wasted->deleteLater();
    wasted->show();
}
