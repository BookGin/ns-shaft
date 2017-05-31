#include "Stair.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <cstdlib>
#include <QPixmap>
#include "Game.h"
#include "Parameter.h"

extern Game * game;

Stair::Stair(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    int random_x = rand() % (CANVAS_WIDTH - STAIR_WIDTH);
    stair_type = (StairType)(rand() % NUM_OF_STAIR_TYPE);
    setPos(random_x,CANVAS_HEIGHT);
    setZValue(STAIR_ITEM_ORDER);
    initPixmap();
}

void Stair::initPixmap() {
    switch(stair_type) {
      case spike_stair:
        setPixmap(QPixmap("images/spike_stair.png").scaled(STAIR_WIDTH, STAIR_HEIGHT)); break;
      case normal_stair:
        setPixmap(QPixmap("images/normal_stair.png").scaled(STAIR_WIDTH, STAIR_HEIGHT)); break;
      case left_roll_stair:
        setPixmap(QPixmap("images/left_roll_stair.png").scaled(STAIR_WIDTH, STAIR_HEIGHT)); break;
      case right_roll_stair:
        setPixmap(QPixmap("images/right_roll_stair.png").scaled(STAIR_WIDTH, STAIR_HEIGHT)); break;
    }
}

int Stair::width() {
    return STAIR_WIDTH;
}

int Stair::height() {
    return STAIR_HEIGHT;
}

void Stair::rise(){
    setPos(x(),y() - STAIR_RISING_SPEED);
}

bool Stair::isOutOfScreen() {
    return (y() + height()) <= 0;
}

void Stair::takeEffect() {
    switch(stair_type) {
      case spike_stair:
        spikeStairEffect(); break;
      case normal_stair:
        normalStairEffect(); break;
      case left_roll_stair:
        leftRollStairEffect(); break;
      case right_roll_stair:
        rightRollStairEffect(); break;
    }
    has_taken_effect = true;
}

void Stair::normalStairEffect() {
    if (!has_taken_effect && game->health->getHealth() < DEFAULT_HEALTH)
        game->health->increase(1);
}

void Stair::spikeStairEffect() {
    if (!has_taken_effect)
        game->health->decrease(5);
}

void Stair::leftRollStairEffect() {
    game->player->setPos(game->player->x() - LEFT_ROLL_STAIR_SPEED,game->player->y());
    if (!has_taken_effect && game->health->getHealth() < DEFAULT_HEALTH)
        game->health->increase(1);
}

void Stair::rightRollStairEffect() {
    if (!has_taken_effect && game->health->getHealth() < DEFAULT_HEALTH)
        game->health->increase(1);
    game->player->setPos(game->player->x() + RIGHT_ROLL_STAIR_SPEED,game->player->y());
}
