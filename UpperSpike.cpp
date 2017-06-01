#include "UpperSpike.h"
#include "Parameter.h"
#include "Game.h"
extern Game * game;

UpperSpike::UpperSpike(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    setPos(0,0);
    setZValue(UPPER_SPIKE_ITEM_ORDER);
    setPixmap(QPixmap("images/upper_spike.png").scaled(CANVAS_WIDTH, UPPER_SPIKE_HEIGHT));
}

void UpperSpike::takeEffect() {
    game->health->decrease(UPPER_SPIKE_DAMAGE);
}
