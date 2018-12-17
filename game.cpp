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
#include <QRandomGenerator>
#include <QFontDatabase>

#include <memory>
static int SCORES;

Game::Game(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Game)
{
  ui->setupUi(this);
  this->setFixedSize(600,800);
  this->setPalette(QPalette(QColor(255,255,255,0)));
  this->setWindowTitle("Galaga");

  for(int i = 0; i < 500; i++){
    std::shared_ptr<SkyStar> star(new SkyStar());
    sky.push_back(star);
  }

  player = new Player();

  int id = QFontDatabase::addApplicationFont(":/images/images/emulogic.ttf");
  QString family = QFontDatabase::applicationFontFamilies(id).at(0);
  emulogic = QFont(family);

  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(40);
}

void Game::newGame()
{
  SCORES =  0;

  for(int i =1; i<9; i++){
      std::shared_ptr<Enemy> enemy (new Enemy(Enemy::Type::Fly,QPoint(50,50) - 50*i*QPoint(1,1),20));
      enemy->addRoute(Route::Path::Line,QPoint(300,400));
      enemy->addRoute(Route::Path::Line,QPoint(600,100));
      enemy->addRoute(Route::Path::Sin,QPoint(200,400));
      enemy->addRoute(Route::Path::Lemniscate);
      enemy->addRoute(Route::Path::Line,QPoint(600,400) + 33*i*QPoint(-1,-1));
      enemy->addRoute(Route::Path::Stay);
      enemies.push_back(enemy);
  }

  for(int i =1; i<9; i++){
      std::shared_ptr<Enemy> enemy (new Enemy(Enemy::Type::Wasp,QPoint(600,800) + 70*i*QPoint(1,1),20));
      enemy->addRoute(Route::Path::Line,QPoint(150,200));
      enemy->addRoute(Route::Path::Sin,QPoint(250,300));
      enemy->addRoute(Route::Path::Lemniscate);
      enemy->addRoute(Route::Path::Line,QPoint(300,100) + 33*i*QPoint(-1,1));
      enemy->addRoute(Route::Path::Stay);
      enemies.push_back(enemy);
  }
  for(int i =1; i<12; i++){
      std::shared_ptr<Enemy> enemy (new Enemy(Enemy::Type::Lobster,QPoint(-800,1600) - 70*i*QPoint(-1,1),20));
      enemy->addRoute(Route::Path::Line,QPoint(600,-50));
      enemy->addRoute(Route::Path::Lemniscate);
      enemy->addRoute(Route::Path::Sin,QPoint(550,400) + 42*i*QPoint(-1,0));
      enemy->addRoute(Route::Path::Stay);
      enemies.push_back(enemy);
  }
}

Game::~Game()
{
  delete ui;
}

void Game::read(const QJsonObject &json)
{
    //player = new Player();
    std::cout <<"Game::read"<<std::endl;
    player->read(json["player"].toObject());
    std::cout <<"Game::read2"<<std::endl;

    QJsonArray enemiesArray = json["enemies"].toArray();
    for (int enemyIndex = 0; enemyIndex < enemiesArray.size(); ++enemyIndex) {
        std::cout <<enemyIndex<<std::endl;
        QJsonObject enemyObject = enemiesArray[enemyIndex].toObject();
        //enemies.insert(enemyIndex,new Enemy());
        enemies[enemyIndex]->read(enemyObject);
    }
}

void Game::write(QJsonObject &json) const
{
    QJsonObject playerObject;
    player->write(playerObject);
    json["player"] = playerObject;

    QJsonArray enemiesArray;
    /*foreach (const Enemy* enemy, enemies) {
        QJsonObject enemyObject;
        enemy->write(enemyObject);
        enemiesArray.append(enemyObject);
    }
    json["enemies"] = enemiesArray;*/
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

void Game::paintEvent(QPaintEvent *)
{
  std::shared_ptr<QPainter> painter (new QPainter(this));
  painter->setCompositionMode(QPainter::CompositionMode::CompositionMode_DestinationOver);
  painter->setPen(Qt::PenStyle::NoPen);
  //draw stars
  for(auto star : sky){
      star->draw(painter);
      star->move();
      //remove old stars
      if (star->getShows() > 50){
         sky.removeOne(star);
         std::shared_ptr<SkyStar> newStar (new SkyStar());
         sky.push_back(newStar);
      }
    }
  //draw player
  //move player
  player->draw(painter);

  player->move();
  //fire if player is firegun
  if(player->isFireGun()){
      player->fire();
  }
  //draw player shots
  for(auto shot : player->getShots()){
      shot->draw(painter);
      shot->move();
    }
  //draw enemies

for(auto enemy : enemies){
      enemy->draw(painter);
      enemy->move();
      enemy->fire();
      enemy->attack(player);

      for(auto shot : enemy->getShots()){
          shot->draw(painter);
          shot->move();
      }

      for(auto shot : player->getShots()){
          if(enemy->collide(shot)){
              std::shared_ptr<Explosion> newExplosion (new Explosion(QPoint(enemy->getRect().x(),enemy->getRect().y())));
              explosions.push_back(newExplosion);
              enemies.removeOne(enemy);
              SCORES++;
              player->removeShot(shot);
              break;
            }
      }
      if(enemy->collide(player)){
          std::shared_ptr<Explosion> newExplosion (new Explosion(QPoint(player->getRect().x(),player->getRect().y())));
          explosions.push_back(newExplosion);
          enemies.removeOne(enemy);
        }
  }
  for(auto explosion : explosions){
      explosion->draw(painter);
      if(explosion->getCurrentFrame() != 4){
          explosion->animate(GameObject::Animation::Stay);
        }
      else{
          explosions.removeOne(explosion);
        }
    }
  painter->setPen(QColor(Qt::red));
  painter->setBrush(QBrush(Qt::BrushStyle::SolidPattern));
  painter->setFont(emulogic);
  painter->drawText(QRect(280,30,200,40),QString::number(SCORES));
}


