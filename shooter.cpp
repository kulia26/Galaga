#include "shooter.h"
#include "shot.h"
#include "game.h"
#include <memory>
#include <cmath>
#include <iostream>
#include"shotpool.h"

void Shooter::removeShot(std::shared_ptr<Shot> shot){
  if(Game::getInstance().getShots().contains(shot) && !Game::getInstance().getShots().isEmpty()){
      Game::getInstance().getShots().removeOne(shot);
    }
}

void Shooter::addShot(std::shared_ptr<Shot> shot){
  if(Game::getInstance().getShots().contains(last)){
      if(shot->getRect().y() - last->getRect().y() > 100){
           Game::getInstance().getShots().push_back(shot);
           last = shot;
        }
    }
  else{
      last = shot;
      Game::getInstance().getShots().push_back(last);
    }
}

QVector<std::shared_ptr<Shot>> Shooter::getShots()
{
  for (auto& shot : Game::getInstance().getShots()){
      if (!shot->isAlive()){
          removeShot(shot);
          break;
      }
  }
  return Game::getInstance().getShots();
}
