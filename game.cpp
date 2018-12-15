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
#include <QJsonArray>
#include <QJsonDocument>

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


  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(40);
}

void Game::newGame()
{
  player = new Player();

  for(int i =1; i<9; i++){
      Enemy* enemy = new Enemy(Enemy::Type::Fly,QPoint(50,50) - 35*i*QPoint(1,1),20);
      enemy->addRoute(new Route(enemy, Route::Path::Line,QPoint(300,400)));
      enemy->addRoute(new Route(enemy, Route::Path::Line,QPoint(600,100)));
      enemy->addRoute(new Route(enemy, Route::Path::Sin,QPoint(200,400)));
      enemy->addRoute(new Route(enemy, Route::Path::Lemniscate));
      enemy->addRoute(new Route(enemy, Route::Path::Line,QPoint(600,400) - 32*i*QPoint(1,1)));
      enemy->addRoute(new Route(enemy, Route::Path::Stay));
      enemies.push_back(enemy);
  }
  for(int i =1; i<9; i++){
      Enemy* enemy = new Enemy(Enemy::Type::Wasp,QPoint(600,800) + 35*i*QPoint(1,1),20);
      enemy->addRoute(new Route(enemy, Route::Path::Line,QPoint(150,200)));
      enemy->addRoute(new Route(enemy, Route::Path::Sin,QPoint(250,300)));
      enemy->addRoute(new Route(enemy, Route::Path::Lemniscate));
      enemy->addRoute(new Route(enemy, Route::Path::Line,QPoint(300,100) + 32*i*QPoint(-1,1)));
      enemy->addRoute(new Route(enemy, Route::Path::Stay));
      enemies.push_back(enemy);
  }
  for(int i =1; i<12; i++){
      Enemy* enemy = new Enemy(Enemy::Type::Lobster,QPoint(-400,1600) - 35*i*QPoint(-1,1),20);
      enemy->addRoute(new Route(enemy, Route::Path::Line,QPoint(600,-50)));
      enemy->addRoute(new Route(enemy, Route::Path::Lemniscate));
      enemy->addRoute(new Route(enemy, Route::Path::Sin,QPoint(550,400) + 35*i*QPoint(-1,0)));
      enemy->addRoute(new Route(enemy, Route::Path::Stay));
      enemies.push_back(enemy);
  }

}

Game::~Game()
{
  delete ui;
}

void Game::read(const QJsonObject &json)
{
    player = new Player();
    std::cout <<"Game::read"<<std::endl;
    player->read(json["player"].toObject());
    std::cout <<"Game::read2"<<std::endl;

    QJsonArray enemiesArray = json["enemies"].toArray();
    for (int enemyIndex = 0; enemyIndex < enemiesArray.size(); ++enemyIndex) {
        std::cout <<enemyIndex<<std::endl;
        QJsonObject enemyObject = enemiesArray[enemyIndex].toObject();
        enemies.insert(enemyIndex,new Enemy());
        enemies[enemyIndex]->read(enemyObject);
    }
}

void Game::write(QJsonObject &json) const
{
    QJsonObject playerObject;
    player->write(playerObject);
    json["player"] = playerObject;

    QJsonArray enemiesArray;
    foreach (const Enemy* enemy, enemies) {
        QJsonObject enemyObject;
        enemy->write(enemyObject);
        enemiesArray.append(enemyObject);
    }
    json["enemies"] = enemiesArray;
}

bool Game::loadGame()
{
  std::cout <<"Game::loadGame"<<std::endl;
    QFile loadFile(QStringLiteral("save.json"));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    read(loadDoc.object());

    return true;
}

bool Game::saveGame() const
{
    QFile saveFile(QStringLiteral("save.json"));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject gameObject;
    write(gameObject);
    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveDoc.toJson());

    return true;
}
// каждый обьект имеет скорость и направление, нажатие кнопок лишь меняет направление
void Game::keyPressEvent(QKeyEvent *event)
{
  // просто задаем нужное направление
  if (event->key() == Qt::Key_Left) {
    player->setCurrentRoute(Route::Path::Left);
  }
  if ( event->key() == Qt::Key_Right ) {
    player->setCurrentRoute(Route::Path::Right);
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
    player->setCurrentRoute(Route::Path::None);
  }
  if ( event->key() == Qt::Key_Space ) {
    player->makeFireGun(false);
  }
}

void Game::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);
  painter.setPen(Qt::PenStyle::NoPen);
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
  //fire if player is firegun
  if(player->isFireGun()){
      player->fire();
  }
  //draw player
  painter.drawPixmap(player->getRect(),player->getPixmap());
  player->move();
  //draw enemies
  for(int i = 0; i < enemies.length(); i++){
      painter.drawPixmap(enemies[i]->getRect(),enemies[i]->getFrame());
      enemies[i]->move();
      //проверяем на коллизии shots и enemies
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
      if(explosions[i]->getCurrentFrame() != 4){
          explosions[i]->animate(GameObject::Animation::Stay);
        }
      else{
          explosions.remove(i);
        }
  }
}


