#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>
#include "Parameter.h"

class Score: public QGraphicsTextItem{
public:
    Score(QGraphicsItem * parent=0);
    void increase(int);
    void decrease(int);
    int getScore();
private:
    int score = DEFAULT_SCORE;
};

#endif // SCORE_H
