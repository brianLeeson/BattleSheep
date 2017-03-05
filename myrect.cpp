#include "myrect.h"
#include <iostream>

void MyRect::keyPressEvent(QKeyEvent *event)
{
    std::cout << "Key pressed!" << std::endl;
    //qDebug() << "MyRect knows that you pressed a key";
}

void MyRect::mousePressEvent(QMouseEvent *event)
{
    std::cout << "Mouse clicked!" << std::endl;
}
