#include "shotpool.h"
#include <iostream>

ShotPool& ShotPool::getInstance(){
    static ShotPool shotPool;
    return shotPool;
}

std::shared_ptr<Shot> ShotPool::createNew(QPoint point, GameObject::Type type)
{
  std::cout << pool.size() << std::endl;
  if(!pool.isEmpty()){
      for(auto pooledShot : pool){
          //std::cout << pooledShot.instance.use_count() << std::endl;
          if(pooledShot.instance.use_count()<=2){
            pooledShot.isUsing = false;
            }
          if(!pooledShot.isUsing && pooledShot.instance->getType() == type){
              pooledShot.isUsing = true;
              pooledShot.instance->reuse(point);
              return pooledShot.instance;
            }
        }
    }
      PooledShot shot;
      std::shared_ptr<Shot> newShot(new Shot(QRect(point,QSize(6,12)), type));
      shot.instance = newShot;
      shot.isUsing = true;
      pool.push_back(shot);
      return shot.instance;
}


