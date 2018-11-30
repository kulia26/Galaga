#include "game.h"
#include "ui_game.h"
#include <QPainter>
#include <QTimer>
#include "skystar.h"
#include "player.h"
#include <QWidget>
#include <QKeyEvent>
#include <QEventLoop>

Game::Game(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Game)
{
  ui->setupUi(this);
  this->setFixedSize(600,800);
  this->setPalette(QPalette(QColor(255,255,255,0)));
  this->setWindowTitle("Galaga");

  for(int i = 0; i < 500; i++){
    sky.push_back(new SkyStar);
  }

  player = new Player();

  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(40);
}

Game::~Game()
{
  delete ui;
}
// каждый обьект имеет скорость и направление, нажатие кнопок лишь меняет направление
void Game::keyPressEvent(QKeyEvent *event)
{
  // просто задаем нужное направление
  if (event->key() == Qt::Key_Left) {
    player->move(GameObject::Direction::left);
  }
  if ( event->key() == Qt::Key_Right ) {
    player->move(GameObject::Direction::right);
  }
  if ( event->key() == Qt::Key_Space ) {
    player->fire();
  }
}

void Game::keyReleaseEvent(QKeyEvent *event)
{
  //меняем направление в нон
}

void Game::paintEvent(QPaintEvent *event)
{
  //Встановлюємо колір вікна в зелений
  //setPalette(QPalette(QPalette::Window,Qt::black));
  QPainter painter(this);
  painter.setPen(Qt::NoPen);
  for(int i = 0; i < sky.size(); i++){
      QBrush brush(sky[i]->color);
      painter.setBrush(brush);
      painter.drawRect(sky[i]->getRect());
      sky[i]->move(GameObject::Direction::bottom);
      if (sky[i]->shows > 35){
         sky.remove(i);
         sky.push_back(new SkyStar());
      }
  }

  // make everything move();
  QVector<Shot*> shots = player->getShots();
  for(int i = 0; i < shots.size(); i++){
      painter.drawPixmap(shots[i]->getRect(),shots[i]->getPixmap());
      shots[i]->move(GameObject::Direction::top);
  }

  painter.drawPixmap(player->getRect(),player->getPixmap());
}


