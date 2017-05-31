#include "Score.h"
#include "Parameter.h"
#include <QFont>

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent){
    setPos(SCORE_TEXT_X,SCORE_TEXT_Y);
    setZValue(TEXT_ITEM_ORDER);

    setPlainText(QString("Score: ") + QString::number(score));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times",16));
}

void Score::increase(int value){
    score += value;
    setPlainText(QString("Score: ") + QString::number(score));
}

void Score::decrease(int value){
    score -= value;
    setPlainText(QString("Score: ") + QString::number(score));
}

int Score::getScore(){
    return score;
}
