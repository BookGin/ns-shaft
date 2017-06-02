#ifndef GAME_H
#define GAME_H

#include <deque>

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QKeyEvent>

#include "Player.h"
#include "Score.h"
#include "Health.h"
#include "Stair.h"
#include "UpperSpike.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game(QWidget * parent=0);

    QGraphicsScene *scene = nullptr;
    Player *player = nullptr;
    Player *player2 = nullptr;
    Score *score = nullptr;
    Health *health = nullptr;
    UpperSpike *upper_spike = nullptr;
    std::deque<Stair*> stairs;
    int key = Qt::Key_No;
    int elapsed_frames = 0;
    int player_num = 1;

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

public slots:
    void updating();

private:
    void createScene();
    void reset();
    void registerUpdatingCallback();
    Stair* getStairWherePlayerStandingOn(Player *player);
    void updatingStairs();
};

#endif // GAME_H
