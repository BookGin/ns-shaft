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
    setScene(scene);    
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(CANVAS_WIDTH,CANVAS_HEIGHT);
}

void Game::reset() {
    if (player) {
        scene->removeItem(player);
        delete player;
    }
    player = new Player();
    scene->addItem(player);

    if (upper_spike) {
        scene->removeItem(upper_spike);
        delete upper_spike;
    }
    upper_spike = new UpperSpike();
    scene->addItem(upper_spike);

    if (score) {
        scene->removeItem(score);
        delete score;
    }
    score = new Score();
    scene->addItem(score);

    if (health) {
        scene->removeItem(health);
        delete health;
    }
    health = new Health();
    scene->addItem(health);

    if (not stairs.empty()) {
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

// We use the name `updating` in case of method name collision.
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
        upper_spike->takeEffect();

    // player move left or right?
    if (key == Qt::Key_Left)
        player->moveLeft();
    if (key == Qt::Key_Right)
        player->moveRight();

    // player rises or falls ?
    Stair *standing_on_stair = getStairWherePlayerStandingOn();
    if (standing_on_stair) {
        standing_on_stair->takeEffect();
        player->setPos(player->x(),standing_on_stair->y() - player->height());
        player->rise();
    } else {
        player->fall();
    }

    // remove, generate and rise stairs
    updatingStairs();

    elapsed_frames++;
}

Stair* Game::getStairWherePlayerStandingOn()
{
    for (Stair *stair: stairs) {
      if (stair->y() > UPPER_SPIKE_HEIGHT + player->height() // touched the upper spikes
          && player->y() + player->height() <= stair->y() // player must be above the stair
          && player->y() + player->height() + player->falling_speed > stair->y() - STAIR_RISING_SPEED // and collision
          && player->x() + player->width() >= stair->x()
          && player->x() + player->width() < stair->x() + stair->width()) {
               return stair;
      }
    }
    return nullptr;
}

void Game::updatingStairs()
{
    Stair *highest_stair = (stairs.size() > 0) ? stairs.front() : nullptr;
    if (highest_stair != nullptr && highest_stair->isOutOfScreen()) {
        scene->removeItem(highest_stair);
        delete highest_stair;
        stairs.pop_front();
    }

    for (Stair *stair : stairs)
        stair->rise();

    if (elapsed_frames % STAIR_GENERATE_PERIOD == 0) {
        Stair *stair = new Stair();
        stairs.push_back(stair);
        scene->addItem(stair);
    }
}
