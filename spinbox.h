#ifndef SPINBOX_H
#define SPINBOX_H

#include <QSpinBox>
#include <QGraphicsRectItem>

class Spinbox: public QSpinBox, public QGraphicsRectItem{
    Q_OBJECT
    public:
        //constructor
        Spinbox(int start, int end, QGraphicsItem *parent);
    signals:
        void valueChanged();
};

#endif // SPINBOX_H
