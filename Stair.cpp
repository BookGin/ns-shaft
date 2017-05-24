#include "Stair.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <cstdlib>
#include "Game.h"
#include "Parameter.h"

extern Game * game;

Stair::Stair(QGraphicsItem *parent): QObject(), QGraphicsRectItem(parent){
    int random_x = rand() % (CANVAS_WIDTH - STAIR_WIDTH);
    setPos(random_x,CANVAS_HEIGHT);
    setRect(0,0,STAIR_WIDTH,STAIR_HEIGHT);
}

void Stair::rise(){
    setPos(x(),y() - STAIR_RISING_SPEED);
}

bool Stair::isOutOfScreen() {
    return (y() + rect().height()) <= 0;
}
