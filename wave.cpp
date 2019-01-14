#include "wave.h"
#include "enemiesfactory.h"
#include<cmath>
Wave::Wave(Type type){
  int j = 5;
  if(type == Type::Easy){
      j = 5;
    }
  if(type == Type::Middle){
      j = 7;
    }
  if(type == Type::Hard){
      j = 8;
    }
  if(type == Type::SuperHard){
      j = 10;
    }
  for(int i =0; i<j; i++){
      std::shared_ptr<Enemy> enemy (EnemiesFactory::newFly(QPoint(600,800) + 40*i*QPoint(1,1),5+j));
      enemy->addRoute(Route::Path::Line,QPoint(150,200));
      enemy->addRoute(Route::Path::HalfCircleRightLeft);
      enemy->addRoute(Route::Path::Line,QPoint(500,200) + 40*i*QPoint(-1,0)+ 10*QPoint(0,i%2+1));
      enemy->addRoute(Route::Path::Stay);
      enemies.push_back(enemy);
  }
  for(int i =0; i<j; i++){
        std::shared_ptr<Enemy> enemy (EnemiesFactory::newWasp(QPoint(-150,-150)+ 40*i*QPoint(-1,-1),5+j));
        enemy->addRoute(Route::Path::Line,QPoint(300,400));
        enemy->addRoute(Route::Path::HalfCircleRightLeft);
        enemy->addRoute(Route::Path::Sin,QPoint(600,400) + 40*i*QPoint(-1,-1));
        enemy->addRoute(Route::Path::Sin,QPoint(550,300));
        enemy->addRoute(Route::Path::Sin,QPoint(500,300) + 45*i*QPoint(-1,0)+ 20*QPoint(0,i%2+1));
        enemy->addRoute(Route::Path::Stay);
        enemies.push_back(enemy);
    }
    for(int i =0; i<j; i++){
        std::shared_ptr<Enemy> enemy (EnemiesFactory::newLobster(QPoint(-800,1600) - 40*i*QPoint(-1,1),5+j));
        enemy->addRoute(Route::Path::Line,QPoint(550,400));
        enemy->addRoute(Route::Path::Line,QPoint(500,400)+ 45*i*QPoint(-1,0) + 40*QPoint(0,i%2));
        enemy->addRoute(Route::Path::Stay);
        enemies.push_back(enemy);
    }
    if(type == Type::SuperHard){
        for(int i =0; i<j; i++){
              std::shared_ptr<Enemy> enemy (EnemiesFactory::newWasp(QPoint(-350,-250)+ 40*i*QPoint(-1,-1),5+j));
              enemy->addRoute(Route::Path::Line,QPoint(200,300));
              enemy->addRoute(Route::Path::Sin,QPoint(450,200));
              enemy->addRoute(Route::Path::Sin,QPoint(400,80) + 45*i*QPoint(-1,0)+ 20*QPoint(0,i%2+1));
              enemy->addRoute(Route::Path::Stay);
              enemies.push_back(enemy);
          }
          for(int i =0; i<j; i++){
              std::shared_ptr<Enemy> enemy (EnemiesFactory::newLobster(QPoint(-800,1600) - 40*i*QPoint(-1,1),5+j));
              enemy->addRoute(Route::Path::Line,QPoint(450,300));
              enemy->addRoute(Route::Path::Line,QPoint(400,300)+ 45*i*QPoint(-1,0) + 40*QPoint(0,i%2));
              enemy->addRoute(Route::Path::Stay);
              enemies.push_back(enemy);
          }
      }
}

QVector<std::shared_ptr<Enemy>>& Wave::getEnemies(){
  return enemies;
}
