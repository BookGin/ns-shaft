#include "Player.h"
#include <QGraphicsScene>
#include <typeinfo>
#include "Stair.h"
#include "Game.h"
#include <QDebug>
#include <QPainter>
#include <QPixmap>
extern Game * game; // there is an external global object called game

Player::Player(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    setPixmap(QPixmap("images/player.png"));
}

void Player::moveLeft() {
    if (x() - left_moving_speed > 0)
        setPos(x()- left_moving_speed, y());
}

void Player::moveRight() {
    if (x() + width() + right_moving_speed < CANVAS_WIDTH)
        setPos(x() + right_moving_speed, y());
}

void Player::fall() {
    setPos(x(),y() + falling_speed);
    falling_speed += PLAYER_FALLING_ACCELERATION;
}

void Player::rise() {
    setPos(x(),y() - STAIR_RISING_SPEED);
    falling_speed = PLAYER_FALLING_SPEED;
}

void Player::resetMovingSpeed() {
    left_moving_speed = PLAYER_MOVING_SPEED;
    right_moving_speed = PLAYER_MOVING_SPEED;
}

int Player::width() {
    return PLAYER_WIDTH;
}

int Player::height() {
    return PLAYER_HEIGHT;
}
