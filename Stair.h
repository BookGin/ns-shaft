#ifndef STAIR_H
#define STAIR_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>

class Stair: public QObject,public QGraphicsRectItem{
    Q_OBJECT
public:
    Stair(QGraphicsItem * parent=0);
    void rise();
    bool isOutOfScreen();
};

#endif
