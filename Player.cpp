#include "Player.h"
#include <QGraphicsScene>
#include <typeinfo>
#include "Stair.h"
#include "Game.h"
#include "Parameter.h"
#include <QDebug>
#include <QPainter>
#include <QPixmap>
extern Game * game; // there is an external global object called game

Player::Player(QGraphicsItem *parent, const char *img): QObject(), QGraphicsPixmapItem(parent){
    setPos(PLAYER_START_POSITION_X,PLAYER_START_POSITION_Y + UPPER_SPIKE_HEIGHT); // generalize to always be in the middle top of screen
    setZValue(PLAYER_ITEM_ORDER);
    setPixmap(QPixmap(img).scaled(PLAYER_WIDTH, PLAYER_HEIGHT));
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

int Player::width() {
    return PLAYER_WIDTH;
}

int Player::height() {
    return PLAYER_HEIGHT;
}
