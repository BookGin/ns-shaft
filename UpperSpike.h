#ifndef UPPERSPIKE_H
#define UPPERSPIKE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class UpperSpike:public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    UpperSpike(QGraphicsItem * parent=0);
};

#endif // UPPERSPIKE_H
