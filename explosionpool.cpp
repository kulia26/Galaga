#include "explosionpool.h"
#include <iostream>

ExplosionPool& ExplosionPool::getInstance(){
    static ExplosionPool _pool;
    return _pool;
}

std::shared_ptr<Explosion> ExplosionPool::createNew(QPoint point)
{
  std::cout << pool.size() << std::endl;
  if(!pool.isEmpty()){
      for(auto pooledExplosion : pool){
          if(pooledExplosion.instance.use_count()<=2){
            pooledExplosion.isUsing = false;
            }
          if(!pooledExplosion.isUsing){
              pooledExplosion.isUsing = true;
              pooledExplosion.instance->reuse(point);
              return pooledExplosion.instance;
            }
        }
    }
      PooledExplosion shot;
      std::shared_ptr<Explosion> newExplosion(new Explosion(point));
      shot.instance = newExplosion;
      shot.isUsing = true;
      pool.push_back(shot);
      return shot.instance;
}
