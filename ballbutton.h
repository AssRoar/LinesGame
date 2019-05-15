#ifndef BALLBUTTON_H
#define BALLBUTTON_H

#include <QPushButton>

class BallButton : public QPushButton
{
    Q_OBJECT

public:
    BallButton();
    void set_color(int color); // 0 - delete
    int now_color;
    int i;
    int j;
signals:
    void Pclk();
};

#endif // BALLBUTTON_H
