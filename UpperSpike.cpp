#include "UpperSpike.h"

UpperSpike::UpperSpike(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    setPixmap(QPixmap("images/spike.png"));
}
