#include "Player.h"
#include <QGraphicsScene>
#include <typeinfo>
#include "Stair.h"
#include "Game.h"
#include <QDebug>
extern Game * game; // there is an external global object called game

Player::Player(QGraphicsItem *parent): QObject(), QGraphicsRectItem(parent){}

void Player::moveLeft() {
    if (x() - PLAYER_MOVING_SPEED > 0)
        setPos(x()- PLAYER_MOVING_SPEED, y());
}

void Player::moveRight() {
    if (x() + rect().width() + PLAYER_MOVING_SPEED < CANVAS_WIDTH)
        setPos(x() + PLAYER_MOVING_SPEED, y());
}

void Player::fall() {
    setPos(x(),y() + falling_speed);
    falling_speed += PLAYER_FALLING_ACCELERATION;
}

void Player::rise() {
    setPos(x(),y() - STAIR_RISING_SPEED);
    falling_speed = PLAYER_FALLING_SPEED;
}
