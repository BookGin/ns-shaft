#include "Game.h"

#include <cstdlib>

#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QTimer>
#include <QDebug>
#include <QObject>
#include <QMessageBox>
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
    key = Qt::Key_No;
    if (player) {
        scene->removeItem(player);
        delete player;
    }
    player = new Player();
    scene->addItem(player);

    if (player2) {
        scene->removeItem(player2);
        delete player2;
        player2 = nullptr;
    }
    if (player_num==2) {
        player2 = new Player(0,"images/player2.png");
        scene->addItem(player2);
    }

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

    if (health2) {
        scene->removeItem(health2);
        delete health2;
        health2 = nullptr;
    }
    if (player_num==2) {
        health2 = new Health(0,HEALTH_TEXT_Y+75);
        scene->addItem(health2);
    }

    if (!stairs.empty()) {
      for (Stair *stair: stairs) {
        scene->removeItem(stair);
        delete stair;
      }
      stairs.clear();
    }
}

void Game::keyPressEvent(QKeyEvent *event) {
    if( event->key() != Qt::Key_W && event->key()!=Qt::Key_Q )
        key = event->key();
    else
        key2 = event->key();
}

void Game::keyReleaseEvent(QKeyEvent * event)
{
    if  (event->key() == Qt::Key_Left && key == Qt::Key_Left && event->isAutoRepeat() == false)
        key = Qt::Key_No;
    else if(event->key() == Qt::Key_Right && key == Qt::Key_Right && event->isAutoRepeat() == false)
        key = Qt::Key_No;
    else if(event->key() == Qt::Key_W && key2 == Qt::Key_W && event->isAutoRepeat() == false)
        key2 = Qt::Key_No;
    else if(event->key() == Qt::Key_Q && key2 == Qt::Key_Q && event->isAutoRepeat() == false)
        key2 = Qt::Key_No;
}

static void ShowMsg(const char *str)
{
    QMessageBox msgBox;
    msgBox.setText(str);
    msgBox.exec();
}

// We use the name `updating` in case of method name collision.
void Game::updating() {
    // player dies?
    if (health->getHealth() <= 0 || player->y() >= CANVAS_HEIGHT) {
        reset();
        if(player_num==1)
            ShowMsg("GG!");
        else
            ShowMsg("P2 Win!");
        return;
    }
    if ( player_num == 2 ) {
        if( health2->getHealth() <= 0 || player2->y() >= CANVAS_HEIGHT )
        {
            reset();
            ShowMsg("P1 Win!");
            return;
        }
    }

    // switch mod?
    if (key == Qt::Key_2)
    {
        player_num = 1 + player_num % 2; // switch between 1 ~ 2
        reset();
        return;
    }

    // paurse?
    if (key == Qt::Key_P)
        return;

    // player get hurted by the upper spikes?
    // Todo: Fix health for 2p
    if (player->y() == UPPER_SPIKE_HEIGHT)
        health->decrease(UPPER_SPIKE_DAMAGE);
    // player move left or right?
    if (key == Qt::Key_Left)
        player->moveLeft();
    if (key == Qt::Key_Right)
        player->moveRight();
    // player2
    if (player_num == 2)
    {
        if (player2->y() == UPPER_SPIKE_HEIGHT)
            health2->decrease(UPPER_SPIKE_DAMAGE);
        if (key2 == Qt::Key_Q)
            player2->moveLeft();
        if (key2 == Qt::Key_W)
            player2->moveRight();
    }

    // player rises or falls ?
    std::vector<std::tuple<Player*,Stair*,Health*>> users;
    users.emplace_back(player,getStairWherePlayerStandingOn(player),health);
    if (player_num == 2)
        users.emplace_back(player2,getStairWherePlayerStandingOn(player2),health2);
    for(auto p:users) {
        auto player = std::get<0>(p);
        auto stair  = std::get<1>(p);
        auto health = std::get<2>(p);
        if( stair ) {
            stair->takeEffect(player,health);
            player->setPos(player->x(),stair->y() - player->height());
            player->rise();
        } else {
            player->fall();
        }
    }

    // remove, generate and rise stairs
    updatingStairs();

    elapsed_frames++;
}

Stair* Game::getStairWherePlayerStandingOn(Player *player)
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
