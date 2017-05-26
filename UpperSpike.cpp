#include "UpperSpike.h"

#include <QBrush>
#include <QColor>

UpperSpike::UpperSpike(QGraphicsItem *parent): QObject(), QGraphicsRectItem(parent){
    setBrush(QBrush(QColor(0, 255, 255)));
}
