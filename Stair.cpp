#include "Stair.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <cstdlib>
#include <QBrush>
#include <QColor>
#include "Game.h"
#include "Parameter.h"

extern Game * game;

Stair::Stair(QGraphicsItem *parent): QObject(), QGraphicsRectItem(parent){
    int random_x = rand() % (CANVAS_WIDTH - STAIR_WIDTH);
    stair_type = (StairType)(rand() % 4);
    setBrush(QBrush(QColor(255, 255 * ((stair_type&2) >> 1), 255 * (stair_type & 1))));
    setPos(random_x,CANVAS_HEIGHT);
    setRect(0,0,STAIR_WIDTH,STAIR_HEIGHT);

}

void Stair::rise(){
    setPos(x(),y() - STAIR_RISING_SPEED);
}

bool Stair::isOutOfScreen() {
    return (y() + rect().height()) <= 0;
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
    if (!has_taken_effect)
        game->health->decrease(-1);
}

void Stair::spikeStairEffect() {
    if (!has_taken_effect)
        game->health->decrease(1);
}

void Stair::leftRollStairEffect() {
    game->player->setPos(game->player->x() - 10,game->player->y());
}

void Stair::rightRollStairEffect() {
    game->player->setPos(game->player->x() + 10,game->player->y());
}
