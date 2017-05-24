#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>

#include "Parameter.h"

class Player:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=0);
    void moveLeft();
    void moveRight();
    int falling_speed = PLAYER_FALLING_SPEED;
    void fall();
    void rise();
};

#endif // PLAYER_H
