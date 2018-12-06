#include "game.h"
#include "ui_game.h"
#include <QPainter>
#include <QTimer>
#include "skystar.h"
#include "player.h"
#include "enemy.h"
#include <QWidget>
#include <QKeyEvent>
#include <QEventLoop>
#include <iostream>
#include <cmath>
#include <QPoint>

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


  enemies.push_back(new Enemy(Enemy::Type::Lobster));
  enemies.push_back(new Enemy(Enemy::Type::Lobster));
  enemies.push_back(new Enemy(Enemy::Type::Lobster));
  enemies.push_back(new Enemy(Enemy::Type::Lobster));
  enemies.push_back(new Enemy(Enemy::Type::Lobster));
  enemies.push_back(new Enemy(Enemy::Type::Lobster));
  enemies.push_back(new Enemy(Enemy::Type::Fly));
  enemies.push_back(new Enemy(Enemy::Type::Wasp));

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
    player->setDirection(GameObject::Direction::left);
  }
  if ( event->key() == Qt::Key_Right ) {
    player->setDirection(GameObject::Direction::right);
  }
  if ( event->key() == Qt::Key_Space ) {
    player->fire();
    if(event->isAutoRepeat()){
        player->makeFireGun(true);
    }
  }



}

void Game::keyReleaseEvent(QKeyEvent *event)
{
  //меняем направление в нон
  if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) {
    player->setDirection(GameObject::Direction::none);
  }
  if ( event->key() == Qt::Key_Space ) {
    player->makeFireGun(false);
  }
}

void Game::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);
  painter.setPen(Qt::NoPen);
  //draw stars
  for(int i = 0; i < sky.size(); i++){
      QBrush brush(sky[i]->getColor());
      painter.setBrush(brush);
      painter.drawRect(sky[i]->getRect());
      sky[i]->move();
      //remove old stars
      if (sky[i]->getShows() > 50){
         sky.remove(i);
         sky.push_back(new SkyStar());
      }
  }
  //draw shots
  for(int i = 0; i < player->getShots().length(); i++){
      painter.drawPixmap(player->getShots()[i]->getRect(),player->getShots()[i]->getPixmap());
      player->getShots()[i]->move();
  }
  //move player
  player->move();
  //fire if player is firegun
  if(player->isFireGun()){
      player->fire();
  }
  //draw player
  painter.drawPixmap(player->getRect(),player->getPixmap());
  //draw enemies
  for(int i = 0; i < enemies.length(); i++){
      painter.drawPixmap(enemies[i]->getRect(),enemies[i]->getFrame());
      enemies[i]->move();
      for(int j = 0; j < player->getShots().length(); j++){
          if(QRect(enemies[i]->getRect() & player->getShots()[j]->getRect()).size() != QSize(0,0)){
              explosions.push_back(new Explosion(QPoint(enemies[i]->getRect().x(),enemies[i]->getRect().y())));
              enemies.remove(i);
              player->removeShot(j);
              break;
            }
      }
  }
  for(int i = 0; i < explosions.length(); i++){
      painter.drawPixmap(explosions[i]->getRect(),explosions[i]->getFrame());
      if(explosions[i]->getFramesCount() != 4){
          explosions[i]->move();
        }
      else{
          explosions.remove(i);
        }

  }



}


