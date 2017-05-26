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
    srand(time(NULL));

    createScene();
    reset();
    registerUpdatingCallback();

    show();
}

void Game::registerUpdatingCallback() {
    QTimer * timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(updating()));
    timer->start(FRAME_DELAY);
}

void Game::createScene() {
    // create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,CANVAS_WIDTH,CANVAS_HEIGHT); // make the scene 800x600 instead of infinity by infinity (default)

    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(CANVAS_WIDTH,CANVAS_HEIGHT);
}

void Game::reset() {
    if (player) {
        scene->removeItem(player);
        delete player;
    }
    player = new Player();
    player->setRect(0,0,PLAYER_WIDTH,PLAYER_HEIGHT); // change the rect from 0x0 (default) to 100x100 pixels
    player->setPos(PLAYER_START_POSITION_X,PLAYER_START_POSITION_Y + UPPER_SPIKE_HEIGHT); // generalize to always be in the middle top of screen
    player->setZValue(PLAYER_ITEM_ORDER);
    scene->addItem(player);

    if (upper_spike) {
        scene->removeItem(upper_spike);
        delete upper_spike;
    }
    upper_spike = new UpperSpike();
    upper_spike->setPos(0,0);
    upper_spike->setRect(0,0,CANVAS_WIDTH,UPPER_SPIKE_HEIGHT);
    upper_spike->setZValue(UPPER_SPIKE_ITEM_ORDER);
    scene->addItem(upper_spike);

    if (score) {
        scene->removeItem(score);
        delete score;
    }
    score = new Score();
    score->setPos(0,50);
    score->setZValue(TEXT_ITEM_ORDER);
    scene->addItem(score);

    if (health) {
        scene->removeItem(health);
        delete health;
    }
    health = new Health();
    health->setPos(0,25);
    score->setZValue(TEXT_ITEM_ORDER);
    scene->addItem(health);

    if (!stairs.empty()) {
      for (Stair *stair: stairs) {
        scene->removeItem(stair);
        delete stair;
      }
      stairs.clear();
    }
}

void Game::keyPressEvent(QKeyEvent *event) {
    key = event->key();
}

void Game::keyReleaseEvent(QKeyEvent * event)
{
    if  (event->key() == Qt::Key_Left && key == Qt::Key_Left && event->isAutoRepeat() == false)
        key = Qt::Key_No;
    else if(event->key() == Qt::Key_Right && key == Qt::Key_Right && event->isAutoRepeat() == false)
        key = Qt::Key_No;
}

void Game::updating() {
    // player dies?
    if (health->getHealth() <= 0 || player->y() >= CANVAS_HEIGHT) {
      reset();
      return;
    }

    // paurse?
    if (key == Qt::Key_P)
        return;

    // player get hurted by the upper spikes?
    if (player->y() == UPPER_SPIKE_HEIGHT)
        health->decrease(UPPER_SPIKE_DAMAGE);

    // player move left or right?
    if (key == Qt::Key_Left)
        player->moveLeft();
    if (key == Qt::Key_Right)
        player->moveRight();

    // player rises or falls ?
    Stair *standing_on_stair = getPlayerStandingOnStair();
    if (standing_on_stair) {
        standing_on_stair->takeEffect();
        player->setPos(player->x(),standing_on_stair->y() - player->rect().height());
        player->rise();
    } else {
        player->resetMovingSpeed();
        player->fall();
    }

    // remove,generate, move stairs
    handleStairs();

    elapsed_frames++;
}

Stair* Game::getPlayerStandingOnStair()
{
    for (Stair *stair: stairs) {
      if (stair->y() > UPPER_SPIKE_HEIGHT + player->rect().height() // touched the upper spikes
          && player->y() + player->rect().height() <= stair->y() // player must be above the stair
          && player->y() + player->rect().height() + player->falling_speed > stair->y() - STAIR_RISING_SPEED // and collision
          && player->x() + player->rect().width() / 2 >= stair->x()
          && player->x() + player->rect().width() / 2 < stair->x() + stair->rect().width()) {
               qDebug() << "on stair!" << "\n";
               return stair;
      }
    }
    return nullptr;
}

void Game::handleStairs()
{
    Stair *highest_stair = (stairs.size() > 0) ? stairs.front() : nullptr;
    if (highest_stair != nullptr && highest_stair->isOutOfScreen()) {
        scene->removeItem(highest_stair);
        delete highest_stair;
        stairs.pop_front();
    }

    for (Stair *stair : stairs)
        stair->rise();

    if (elapsed_frames % 24 == 0) {
        Stair *stair = new Stair();
        stair->setZValue(STAIR_ITEM_ORDER);
        stairs.push_back(stair);
        scene->addItem(stair);
    }
}
