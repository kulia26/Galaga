#include "game.h"
#include "gameobject.h"
#include "ui_game.h"
#include <QPainter>
#include <QTimer>
#include "skystar.h"
#include "player.h"
#include "enemiesfactory.h"
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
#include <QTextStream>
#include <QFontDatabase>
#include <memory>
#include"explosionpool.h"
#include"wave.h"
#include <fstream>

static long int SCORES;
static long int HIGHSCORE;

Game::Game(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Game)
{
  ui->setupUi(this);
  this->setFixedSize(600,800);
  this->setPalette(QPalette(QColor(255,255,255,0)));
  this->setWindowTitle("Galaga");

  sky.reserve(500);
  for(int i = 0; i < 500; i++){
    std::shared_ptr<SkyStar> star(new SkyStar());
    sky.push_back(star);
  }

  int id = QFontDatabase::addApplicationFont(":/images/images/emulogic.ttf");
  QString family = QFontDatabase::applicationFontFamilies(id).at(0);
  emulogic = QFont(family);
  this->setFont(emulogic);
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  COUNTER = 0;
  GETREADY = 4;

  QFile highscore(":/data/data/highscore.txt");
  highscore.open(QIODevice::ReadOnly | QIODevice::Text);
  QTextStream ts(&highscore);
  HIGHSCORE  = ts.readLine().toLong();
  highscore.close();

  timer->start(35);

}
void Game::closeEvent(QCloseEvent *event){
  std::ofstream myfile;
  myfile.open ("/home/kulia26/cpp/Galaga2/data/highscore.txt");
  myfile << HIGHSCORE;
  myfile.close();
  event->accept();
}

Game& Game::getInstance(){
  static Game game{};
    return game;
}

QVector<std::shared_ptr<Shot>>& Game::getShots(){
  return shots;
}

long int& Game::getCounter(){
  return COUNTER;
}

void Game::newGame()
{
  SCORES =  0;
  state  = State::Play;
  players.clear();
  enemies.clear();
  explosions.clear();
  shots.clear();
  waves.clear();
  for (int i = 0; i<5; i++){
    std::shared_ptr<Player> player (new Player());
    players.push_back(player);
  }

  this->player = players.first();

  std::shared_ptr<Wave> wave1 (new Wave(Wave::Type::Easy));
  waves.push_back(wave1);

  std::shared_ptr<Wave> wave2 (new Wave(Wave::Type::Middle));
  waves.push_back(wave2);

  std::shared_ptr<Wave> wave3 (new Wave(Wave::Type::Hard));
  waves.push_back(wave3);

  std::shared_ptr<Wave> wave4 (new Wave(Wave::Type::SuperHard));
  waves.push_back(wave4);

  enemies.append(waves.first()->getEnemies());
  explosions.clear();
  shots.clear();
  drawable.clear();
  physical.clear();


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
        QJsonObject enemyObject = enemiesArray[enemyIndex].toObject();
        //enemies.insert(enemyIndex,new Enemy());
        enemies[enemyIndex]->read(enemyObject);
    }
}

void Game::write(QJsonObject &json) const
{
    QJsonObject playerObject;
    //player->write(playerObject);
    json["player"] = playerObject;

    //QJsonArray enemiesArray;
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
  if ((event->key() == Qt::Key_Down || event->key() == Qt::Key_Up) && state==State::Menu) {
      if(menuItem == Menu::Exit){
          menuItem = Menu::NewGame;
        }else{
          menuItem = Menu::Exit;
        }
  }
  if (event->key() == Qt::Key_Space && state==State::Menu){
      std::cout<<"Enter is press"<<std::endl;
      if(menuItem == Menu::Exit){
          event->accept();
          this->close();

        }else{
          this->newGame();
        }
  }
  if (event->key() == Qt::Key_Space && (state==State::YouWin || state ==State::GameOver)){
      changeState(State::Menu);
      drawable.clear();
  }
  if(state == State::Play){
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

}

void Game::keyReleaseEvent(QKeyEvent *event)
{
  //меняем направление в нон
  if(state == State::Play){
      if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) {
        player->setCurrentRoute(Route::Path::None);
      }
      if ( event->key() == Qt::Key_Space ) {
        player->makeFireGun(false);
      }
    }

}
void Game::changeState(State state){
  if(state == State::GameOver){
      this->timer->setInterval(35);
    }
  this->state = state;
}
void Game::executePlay(){

  for(auto& star : sky){
      //remove old stars
      if(!star->isAlive()){
          star->reborn();
        }else{
          star->move();
          if(!drawable.contains(star)){
              drawable.append(star);
            }
        }
    }

  resolveCollisions();

  if(!drawable.contains(player)){
      drawable.append(player);
    }

  if(!physical.contains(player) ){
      physical.append(player);
    }

  for(auto& shot : shots){
      if(shot->isAlive()){
          shot->move();
          if(!drawable.contains(shot)){
              drawable.append(shot);
            }
          if(!physical.contains(shot)){
              physical.append(shot);
            }
        }
      else{
          drawable.removeOne(shot);
          shots.removeOne(shot);
        }
    }

  for(auto& enemy : enemies){
      if(enemy->isAlive()){
          enemy->move();
          enemy->attack(player);
          if(!drawable.contains(enemy)){
              drawable.append(enemy);
            }
          if(!physical.contains(enemy)){
              physical.append(enemy);
            }
        }
      else{
          drawable.removeOne(enemy);
          enemies.removeOne(enemy);
        }
  }

  for(auto explosion : explosions){
      if(explosion->isAlive()){
          if(!drawable.contains(explosion)){
              drawable.append(explosion);
            }
          explosion->animate(Animated::Animation::Stay);
        }
      else{
          drawable.removeOne(explosion);
          explosions.removeOne(explosion);
          break;
        }
    }
  if(enemies.length() < 3){
      nextWave();
    }
  if(player->isAlive()){
      player->move();
    }else{
      this->changeState(State::PlayerHurt);
    }
  if(enemies.isEmpty()){
      changeState(State::YouWin);
    }
}

void Game::executePlayerHurt(){

  this->timer->setInterval(200);
  if(drawable.contains(player)){
      drawable.removeOne(player);
    }

  for(auto explosion : explosions){
      if(explosion->isAlive()){
          if(!drawable.contains(explosion)){
              drawable.append(explosion);
            }
          explosion->animate(Animated::Animation::Stay);
        }
      else{
          drawable.removeOne(explosion);
          explosions.removeOne(explosion);
          break;
        }
    }
  if(explosions.isEmpty()){

      QPoint pos = players.first()->getPoint();
      players.removeFirst();
      if(!players.isEmpty()){
          player = players.first();
          player->moveRectTo(pos);
          drawable.append(player);
          changeState(State::GetReady);
        }else{
          changeState(State::GameOver);
        }
    }
}

void Game::executeGetReady(){
  --GETREADY;
  this->timer->setInterval(600);
  if(GETREADY == 0){
      changeState(State::Play);
      GETREADY = 4;
      this->timer->setInterval(35);
      return;
    }
}
void Game::executeGameOver(){

  for(auto& enemy : enemies){
      if(enemy->isAlive()){
          enemy->move();
          if(!drawable.contains(enemy)){
              drawable.append(enemy);
            }
        }
      else{
          drawable.removeOne(enemy);
          enemies.removeOne(enemy);
        }
  }
  for(auto& shot : shots){
      if(shot->isAlive()){
          shot->move();
          if(!drawable.contains(shot)){
              drawable.append(shot);
            }
          if(!physical.contains(shot)){
              physical.append(shot);
            }
        }
      else{
          drawable.removeOne(shot);
          shots.removeOne(shot);
        }
    }
  if(explosions.length()< 14){
      explosions.push_back(ExplosionPool::getInstance().createNew(QPoint(QRandomGenerator::global()->bounded(0,600),QRandomGenerator::global()->bounded(0,800)),Explosion::Type::EnemyDie));
    }
  for(auto explosion : explosions){
      if(explosion->isAlive()){
          if(!drawable.contains(explosion)){
              drawable.append(explosion);
            }
          explosion->animate(Animated::Animation::Stay);
        }
      else{
          drawable.removeOne(explosion);
          explosions.removeOne(explosion);
          break;
        }
    }
}
void Game::executeYouWin(){
  for(auto& shot : shots){
          drawable.removeOne(shot);
          shots.removeOne(shot);
        }

  if(explosions.length()< 14){
      explosions.push_back(ExplosionPool::getInstance().createNew(QPoint(QRandomGenerator::global()->bounded(0,600),QRandomGenerator::global()->bounded(0,800)),Explosion::Type::EnemyDie));
    }
  for(auto explosion : explosions){
      if(explosion->isAlive()){
          if(!drawable.contains(explosion)){
              drawable.append(explosion);
            }
          explosion->animate(Animated::Animation::Stay);
        }
      else{
          drawable.removeOne(explosion);
          explosions.removeOne(explosion);
          break;
        }
    }
}

void Game::executeMenu(){
  for(auto& star : sky){
    //remove old stars
    if(!star->isAlive()){
        star->reborn();
      }else{
        star->move();
        if(!drawable.contains(star)){
            drawable.append(star);
          }
      }
  }
}

void Game::execute(){
  COUNTER++;
  if(SCORES > HIGHSCORE){
      HIGHSCORE = SCORES;
    }
  if(state == State::Play){
      this->executePlay();
    }
  if(state==State::PlayerHurt){
      this->executePlayerHurt();
    }
  if(state==State::GetReady){
      this->executeGetReady();
    }
  if(state==State::GameOver){
      this->executeGameOver();
    }
  if(state==State::YouWin){
      this->executeYouWin();
    }
  if(state == State::Menu){
      this->executeMenu();
    }


}
void Game::nextWave(){
  if(waves.length()>1){
      waves.removeFirst();
      std::cout<<"Next wave ! "<< waves.first()->getEnemies().length() << " enemies is comming"<<std::endl;
      enemies.append(waves.first()->getEnemies());
      return;
    }
  if(enemies.isEmpty()){
        changeState(State::YouWin);
    }
}


void Game::resolveCollisions()
{
  for(auto& physicalObject1 : physical){
      for (auto physicalObject2 = physicalObject1; physicalObject2 != physical.last(); physicalObject2 = physical[physical.indexOf(physicalObject2)+1]){
          if(physicalObject1 != physicalObject2 && physical.contains(physicalObject2)){
              if(physicalObject1->collide(physicalObject2)){
                  makeDemage(physicalObject1,physicalObject2);
                  std::shared_ptr<Explosion> newExplosion(makeExplosion(physicalObject1, physicalObject2));
                  if(newExplosion != nullptr){
                      explosions.push_back(newExplosion);
                    }
                  physical.removeOne(physicalObject2);
                  //break;
                }
            }
        }
      if(!physicalObject1->isAlive()){
          physical.removeOne(physicalObject1);
          //break;
        }
    }
}

void Game::makeDemage(std::shared_ptr<PhysicalObject> object1, std::shared_ptr<PhysicalObject> object2){
  if(object1->getType() == GameObject::Type::PlayerShot || object2->getType() == GameObject::Type::PlayerShot ){
      if(object1->getType() == GameObject::Type::Enemy || object2->getType() == GameObject::Type::Enemy ){
          object1->hurt();
          object2->hurt();
          SCORES++;
        }
    }
  if(object1->getType() == GameObject::Type::EnemyShot || object2->getType() == GameObject::Type::EnemyShot ){
      if(object1->getType() == GameObject::Type::Player || object2->getType() == GameObject::Type::Player ){
          object1->hurt();
          object2->hurt();
        }
    }
}

std::shared_ptr<Explosion> Game::makeExplosion(std::shared_ptr<PhysicalObject> object1, std::shared_ptr<PhysicalObject> object2){
  if(!object1->isAlive() && object1->getType() == GameObject::Type::Enemy){
      return ExplosionPool::getInstance().createNew(object1->getPoint(), Explosion::Type::EnemyDie);
    }
  if(!object2->isAlive() && object2->getType() == GameObject::Type::Enemy){
      return ExplosionPool::getInstance().createNew(object2->getPoint(), Explosion::Type::EnemyDie);
    }
  if(!object1->isAlive() && object1->getType() == GameObject::Type::Player){
      return ExplosionPool::getInstance().createNew(object1->getPoint(), Explosion::Type::PlayerDie);
    }
  if(!object2->isAlive() && object2->getType() == GameObject::Type::Player){
      return ExplosionPool::getInstance().createNew(object2->getPoint(), Explosion::Type::PlayerDie);
    }
  return nullptr;
}

void Game::paintEvent(QPaintEvent *)
{
  execute();
  std::shared_ptr<QPainter> painter (new QPainter(this));
  painter->setCompositionMode(QPainter::CompositionMode::CompositionMode_DestinationOver);
  painter->setPen(Qt::PenStyle::NoPen);

  for(auto& drawedObject : drawable){
      drawedObject->draw(painter);
    }

  painter->setPen(QColor(Qt::gray).lighter());
  painter->setBrush(QBrush(Qt::BrushStyle::SolidPattern));
  painter->drawText(QRect(25,25,200,40),QString::number(SCORES));
  painter->drawText(QRect(255,25,200,40),QString::number(HIGHSCORE));
  painter->setPen(QColor(Qt::red));
  painter->drawText(QRect(220,5,200,40),QString("HIGH SCORE"));
  if(state==State::GetReady){
      QFont big = emulogic;
      big.setPixelSize(72);
      painter->setFont(big);
      painter->setCompositionMode(QPainter::CompositionMode::CompositionMode_Darken);
      painter->setPen(Qt::PenStyle::NoPen);
      painter->setBrush(QBrush(QColor(0,0,0,180)));
      painter->drawRect(0,0,600,800);
      painter->setPen(QColor(Qt::red));
      painter->setCompositionMode(QPainter::CompositionMode::CompositionMode_Lighten);
      painter->drawText(QPoint(250,350),QString::number(GETREADY));
    }
  if(state==State::GameOver){
      QFont big = emulogic;
      big.setPixelSize(24);
      painter->setFont(big);
      painter->setCompositionMode(QPainter::CompositionMode::CompositionMode_Darken);
      painter->setPen(Qt::PenStyle::NoPen);
      painter->setBrush(QBrush(QColor(0,0,0,180)));
      painter->drawRect(0,0,600,800);
      painter->setPen(QColor(Qt::red));
      painter->setCompositionMode(QPainter::CompositionMode::CompositionMode_Lighten);
      painter->drawText(QPoint(140,350),QString("Game Over !"));
      painter->drawText(QPoint(140,400),QString("Your score is: "));
      painter->drawText(QPoint(140,440),QString::number(SCORES));
    }
  if(state==State::YouWin){
      QFont big = emulogic;
      big.setPixelSize(24);
      painter->setFont(big);
      painter->setCompositionMode(QPainter::CompositionMode::CompositionMode_Darken);
      painter->setPen(Qt::PenStyle::NoPen);
      painter->setBrush(QBrush(QColor(0,0,0,180)));
      painter->drawRect(0,0,600,800);
      painter->setPen(QColor(Qt::red));
      painter->setCompositionMode(QPainter::CompositionMode::CompositionMode_Lighten);
      painter->drawText(QPoint(140,350),QString("You Win !"));
      painter->drawText(QPoint(140,400),QString("Your score is: "));
      painter->drawText(QPoint(140,440),QString::number(SCORES));
    }

  if(state==State::Menu){
      painter->setCompositionMode(QPainter::CompositionMode::CompositionMode_SourceOver);
      painter->drawPixmap(QPoint(100,170), QPixmap(":/images/images/logo.png").scaledToWidth(400));
      painter->drawText(QPoint(200,450), QString("New game"));
      painter->drawText(QPoint(200,500), QString("Exit"));
      painter->setBrush(QBrush(Qt::red));

      QPointF pos;
      if(menuItem == Menu::NewGame){
          pos = QPoint(175,423);
        }
      if(menuItem == Menu::Exit){
          pos = QPoint(175,474);
        }
      QPointF points[3] = {
          QPointF(15.0, 25.0)+pos,
          QPointF(15.0, 15.0)+pos,
          QPointF(20.0, 20.0)+pos
      };
      painter->drawPolygon(points, 3);


    }
  if(state != State::Menu){
      for(int i = 0; i < players.length(); i++){
          painter->drawPixmap(QRect(10+32*i,765,24,24),player->getPixmap());
        }
    }

}


