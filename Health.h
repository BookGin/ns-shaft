#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>

#include "Parameter.h"

class Health: public QGraphicsTextItem{
public:
    Health(QGraphicsItem * parent=0, int pos_y=HEALTH_TEXT_Y);
    void increase(int);
    void decrease(int);
    int getHealth();
private:
    int health = DEFAULT_HEALTH;
};

#endif // HEALTH_H
