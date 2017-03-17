#include "spinbox.h"

Spinbox::Spinbox(int s, int e, QGraphicsItem *parent): QGraphicsRectItem(parent){
    this->setRange(s, e);
    this->setSingleStep(1);
    this->setValue(s);
    this->setFixedHeight(50);
    this->setFixedWidth(200);
    this->setAlignment(Qt::AlignHCenter);
}
