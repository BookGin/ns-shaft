#ifndef STAIR_H
#define STAIR_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>

enum StairType {
    normal_stair, spike_stair, left_roll_stair, right_roll_stair
};

class Stair: public QObject,public QGraphicsRectItem{
    Q_OBJECT
public:
    Stair(QGraphicsItem * parent=0);
    void rise();
    bool isOutOfScreen();
    void takeEffect();
private:
    bool has_taken_effect = false;
    StairType stair_type;

    void normalStairEffect();
    void spikeStairEffect();
    void leftRollStairEffect();
    void rightRollStairEffect();
};

#endif
