#include "Health.h"
#include "Parameter.h"
#include <QFont>

Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent){
    setPos(HEALTH_TEXT_X,HEALTH_TEXT_Y);
    setZValue(TEXT_ITEM_ORDER);

    setPlainText(QString("Health: ") + QString::number(health));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
}

void Health::increase(int value){
    health += value;
    setPlainText(QString("Health: ") + QString::number(health));
}

void Health::decrease(int value){
    health -= value;
    setPlainText(QString("Health: ") + QString::number(health));
}

int Health::getHealth(){
    return health;
}

