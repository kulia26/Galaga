#ifndef WAVE_H
#define WAVE_H
#include<memory>
#include"QVector"
#include"enemy.h"

class Wave
{
public:
  enum class Type{Easy,Middle,Hard,SuperHard};
  explicit Wave(Type type);
  QVector<std::shared_ptr<Enemy>>& getEnemies();
private:
  QVector<std::shared_ptr<Enemy>> enemies;
};

#endif // WAVE_H
