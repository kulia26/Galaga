#ifndef EXPLOSIONPOOL_H
#define EXPLOSIONPOOL_H
#include"explosion.h"

class ExplosionPool
{
public:
  std::shared_ptr<Explosion> createNew(QPoint point);
  static ExplosionPool& getInstance();
private:
  struct PooledExplosion{
    std::shared_ptr<Explosion> instance;
    bool isUsing;
  };
  QVector<PooledExplosion> pool;
  ExplosionPool() = default;
  ExplosionPool(ExplosionPool const&) = delete;
  ~ExplosionPool() = default;
  ExplosionPool& operator= (ExplosionPool const&) = delete;
};

#endif // EXPLOSIONPOOL_H
