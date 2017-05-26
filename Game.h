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

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game(QWidget * parent=0);

    QGraphicsScene *scene = nullptr;
    Player *player = nullptr;
    Score *score = nullptr;
    Health *health = nullptr;
    std::deque<Stair*> stairs;
    int key = Qt::Key_No;
    int elapsed_frames = 0;

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

public slots:
    void updating();

private:
    void createScene();
    void resetPlayerScoreHealthStairs();
    void registerUpdatingCallback();
    Stair* getPlayerStandingOnStair();
    void handleStairs();
};

#endif // GAME_H
