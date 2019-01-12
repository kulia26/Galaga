#ifndef SHOTPOOL_H
#define SHOTPOOL_H

#include"shot.h"

class ShotPool
{
public:
  std::shared_ptr<Shot> createNew(QPoint point, GameObject::Type type);
  static ShotPool& getInstance();
private:
  struct PooledShot{
    std::shared_ptr<Shot> instance;
    bool isUsing;
  };
  QVector<PooledShot> pool;
  ShotPool() = default;
  ShotPool(ShotPool const&) = delete;
  ~ShotPool() = default;
  ShotPool& operator= (ShotPool const&) = delete;
};

#endif // SHOTPOOL_H
