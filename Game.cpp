#include "Game.h"

#include <cstdlib>

#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QTimer>
#include <QDebug>
#include <QObject>
#include <ctime>
#include <cstdlib>
#include "Stair.h"
#include "Parameter.h"

Game::Game(QWidget *parent) {
    // create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,CANVAS_WIDTH,CANVAS_HEIGHT); // make the scene 800x600 instead of infinity by infinity (default)

    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(CANVAS_WIDTH,CANVAS_HEIGHT);

    // create the player
    player = new Player();
    player->setRect(0,0,PLAYER_WIDTH,PLAYER_HEIGHT); // change the rect from 0x0 (default) to 100x100 pixels
    player->setPos(PLAYER_START_POSITION_X,PLAYER_START_POSITION_Y); // generalize to always be in the middle top of screen

    /* make the player focusable and set it to be the current focus
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus(); */

    // add the player to the scene
    scene->addItem(player);

    // create the score/health
    score = new Score();
    scene->addItem(score);
    health = new Health();
    health->setPos(health->x(),health->y()+25);
    scene->addItem(health);

    srand(time(NULL));

    QTimer * timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(updating()));
    timer->start(50);

    show();
}

void Game::keyPressEvent(QKeyEvent *event) {
    key = event->key();
}

void Game::keyReleaseEvent(QKeyEvent * event)
{
    // Gin: I don't know why it works
    if  (event->key() == Qt::Key_Left && key == Qt::Key_Left && event->isAutoRepeat() == false)
        key = Qt::Key_No;
    else if(event->key() == Qt::Key_Right && key == Qt::Key_Right && event->isAutoRepeat() == false)
        key = Qt::Key_No;
}

void Game::updating() {
    static int loop_times = 0;

    if (key == Qt::Key_Left)
        player->moveLeft();
    if (key == Qt::Key_Right)
        player->moveRight();
    if (key == Qt::Key_P)
        return;

    // player dies?
    if (health->getHealth() <= 0 || player->y() >= CANVAS_HEIGHT)
        return;

    // player get hurted by the upper spikes?
    if (player->y() == 0)
        health->decrease(UPPER_SPIKE_DAMAGE);

    // player rises or falls
    bool is_on_stair = false;
    for (Stair *stair : stairs) {
      if (stair->y() >= 0 + player->rect().height() // touched the upper spikes
          && player->y() + player->rect().height() <= stair->y() // player must be above the stair
          && player->y() + player->rect().height() + player->falling_speed > stair->y() - STAIR_RISING_SPEED // and collision
          && player->x() + player->rect().width() / 2 >= stair->x()
          && player->x() + player->rect().width() / 2 < stair->x() + stair->rect().width()) {
               qDebug() << "on stair!" << rand() << "\n";
               is_on_stair = true;
               player->setPos(player->x(),stair->y() - player->rect().height());
               break;
      }
    }


    if (is_on_stair)
        player->rise();
    else
        player->fall();

    Stair *highest_stair = (stairs.size() > 0) ? stairs.front() : nullptr;
    if (highest_stair != nullptr && highest_stair->isOutOfScreen()) {
        scene->removeItem(highest_stair);
        delete highest_stair;
        stairs.pop_front();
    }

    for (Stair *stair : stairs)
        stair->rise();

    if (loop_times % 30 == 0) {
        Stair *stair = new Stair();
        stairs.push_back(stair);
        scene->addItem(stair);
    }

    loop_times ++;
}

