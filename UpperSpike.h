#ifndef UPPERSPIKE_H
#define UPPERSPIKE_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>

class UpperSpike:public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    UpperSpike(QGraphicsItem * parent=0);
};

#endif // UPPERSPIKE_H
