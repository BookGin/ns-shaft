#include "UpperSpike.h"
#include "Parameter.h"

UpperSpike::UpperSpike(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    setPos(0,0);
    setZValue(UPPER_SPIKE_ITEM_ORDER);
    setPixmap(QPixmap("images/spike.png").scaled(CANVAS_WIDTH, UPPER_SPIKE_HEIGHT));
}
