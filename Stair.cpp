#include "Stair.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <cstdlib>
#include <QPixmap>
#include "Game.h"
#include "Parameter.h"

extern Game * game;

Stair::Stair(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    int random_x = rand() % (CANVAS_WIDTH - STAIR_WIDTH);
    stair_type = (StairType)(rand() % NUM_OF_STAIR_TYPE);
    setPos(random_x,CANVAS_HEIGHT);
    setZValue(STAIR_ITEM_ORDER);
    initPixmap();
}

void Stair::initPixmap() {
    switch(stair_type) {
      case spike_stair:
        setPixmap(QPixmap("images/spike_stair.png").scaled(STAIR_WIDTH, STAIR_HEIGHT)); break;
      case normal_stair:
        setPixmap(QPixmap("images/normal_stair.png").scaled(STAIR_WIDTH, STAIR_HEIGHT)); break;
      case left_roll_stair:
        setPixmap(QPixmap("images/left_roll_stair.png").scaled(STAIR_WIDTH, STAIR_HEIGHT)); break;
      case right_roll_stair:
        setPixmap(QPixmap("images/right_roll_stair.png").scaled(STAIR_WIDTH, STAIR_HEIGHT)); break;
    }
}

int Stair::width() {
    return STAIR_WIDTH;
}

int Stair::height() {
    return STAIR_HEIGHT;
}

void Stair::rise(){
    setPos(x(),y() - STAIR_RISING_SPEED);
}

bool Stair::isOutOfScreen() {
    return (y() + height()) <= 0;
}

void Stair::takeEffect() {
    switch(stair_type) {
      case spike_stair:
        spikeStairEffect(); break;
      case normal_stair:
        normalStairEffect(); break;
      case left_roll_stair:
        leftRollStairEffect(); break;
      case right_roll_stair:
        rightRollStairEffect(); break;
    }
    has_taken_effect = true;
}

void Stair::normalStairEffect() {
    // 正常的 Stair
    // 如果玩家 HP 沒滿，那麼增加一點生命值
}

void Stair::spikeStairEffect() {
    if (!has_taken_effect)
        game->health->decrease(5); // If the health is negative, updating() in Game.cpp will regard it as death
}

void Stair::leftRollStairEffect() {
    // 向左捲動的 stair
    // 如果玩家 HP 沒滿，那麼增加一點生命值
    // 將玩家位置設定為，目前位置往左移 LEFT_ROLL_STAIR_SPEED 單位的距離
}

void Stair::rightRollStairEffect() {
    // 向右捲動的 stair
    // 如果玩家 HP 比預設的血量小，那麼增加一點生命值
    // 將玩家位置設定為，目前位置往右移 RIGHT_ROLL_STAIR_SPEED 單位的距離
}
