#ifndef STAIR_H
#define STAIR_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

enum StairType {
    normal_stair, spike_stair, left_roll_stair, right_roll_stair,
    NUM_OF_STAIR_TYPE // This value is intented to keep the number of elements in this enum.
};

class Stair: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Stair(QGraphicsItem * parent=0);
    void rise();
    bool isOutOfScreen();
    void takeEffect();
    int width();
    int height();

private:
    void initPixmap();
    bool has_taken_effect = false;
    StairType stair_type;

    void normalStairEffect();
    void spikeStairEffect();
    void leftRollStairEffect();
    void rightRollStairEffect();
};

#endif
