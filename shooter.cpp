#include "shooter.h"
#include "shot.h"
#include <memory>
#include <cmath>
#include <iostream>

Shooter::Shooter()
{
  shots.reserve(10);
}

Shooter::~Shooter(){
  shots.clear();
}

void Shooter::fire(){

}

void Shooter::removeShot(std::shared_ptr<Shot> shot){
  if(shots.contains(shot) && !shots.isEmpty()){
      shots.removeOne(shot);
    }
}

void Shooter::addShot(std::shared_ptr<Shot> shot){

  if(shots.isEmpty()){
      shots.push_back(shot);
    }else{
      if(std::abs(shots.last()->getPoint().y() - shot->getPoint().y()) > 100){
          shots.push_back(shot);
        }
    }
}

QVector<std::shared_ptr<Shot>> Shooter::getShots()
{
  for (auto& shot : shots){
      if (!shot->isAlive()){
          removeShot(shot);
          break;
      }
  }
  return shots;
}
