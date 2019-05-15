#include <mainwindow.h>


int MainWindow::del(int x, int y)
{
    int answ=0;
    int col=pole[x][y]->now_color;
    int colnow=col;
    //ГОРИЗОНТАЛЬНЫЙ DEL
    {
        int xx=x;
        int yy=y;
        int shl=0;
        while ((--yy>=0)&&(pole[xx][yy]->now_color==pole[x][y]->now_color))
            shl++;
        yy=y;
        int shr=0;
        while ((++yy<=8)&&(pole[xx][yy]->now_color==pole[x][y]->now_color))
            shr++;
        if (shr+shl+1>=5)
        {
            colnow=0;
            for (int i=y-shl;i<=y+shr;i++) {pole[xx][i]->set_color(0);++answ;} answ--;
        }

    }
    pole[x][y]->set_color(col);
    //ВЕРТИКАЛЬНЫЙ DEL
    {
        int xx=x;
        int yy=y;
        int svu=0;
        while ((--xx>=0)&&(pole[xx][yy]->now_color==pole[x][y]->now_color))
            svu++;
        xx=x;
        int svd=0;
        while ((++xx<=8)&&(pole[xx][yy]->now_color==pole[x][y]->now_color))
            svd++;
        if (svu+svd+1>=5)
        {
            colnow=0;
            for (int i=x-svu;i<=x+svd;i++) {pole[i][yy]->set_color(0);++answ;} answ--;
        }

    }
    pole[x][y]->set_color(col);
    // \ DEL
    {
        int xx=x;
        int yy=y;
        int sbu=0;
        while ((--xx>=0)&&(--yy>=0)&&(pole[xx][yy]->now_color==pole[x][y]->now_color))
            sbu++;
        xx=x;
        yy=y;
        int sbd=0;
        while ((++xx<=8)&&(++yy<=8)&&(pole[xx][yy]->now_color==pole[x][y]->now_color))
            sbd++;
        if (sbu+sbd+1>=5)
        {
            colnow=0;
            for (int i=-sbu;i<=sbd;i++) {pole[x+i][y+i]->set_color(0);++answ;} answ--;
        }

    }
    pole[x][y]->set_color(col);
    // / DEL
    {
        int xx=x;
        int yy=y;
        int ssu=0;
        while ((--xx>=0)&&(++yy>=0)&&(pole[xx][yy]->now_color==pole[x][y]->now_color))
            ssu++;
        xx=x;
        yy=y;
        int ssd=0;
        while ((++xx<=8)&&(--yy<=8)&&(pole[xx][yy]->now_color==pole[x][y]->now_color))
            ssd++;
        if (ssu+ssd+1>=5)
        {
            colnow=0;
            for (int i=-ssu;i<=ssd;i++) {pole[x+i][y-i]->set_color(0);++answ;} answ--;
        }
    }
    if (answ) answ++;
    pole[x][y]->set_color(colnow);
    return answ;
}
