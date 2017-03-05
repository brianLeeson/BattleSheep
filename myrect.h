#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>
#include <QMouseEvent>

class MyRect: public QGraphicsRectItem {
public:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // MYRECT_H
