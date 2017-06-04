#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include "Parameter.h"

class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=0,const char *img="images/player.png");
    int left_moving_speed = PLAYER_MOVING_SPEED;
    int right_moving_speed = PLAYER_MOVING_SPEED;
    void moveLeft();
    void moveRight();

    int falling_speed = PLAYER_FALLING_SPEED;
    void fall();
    void rise();
    int width();
    int height();
};

#endif // PLAYER_H
