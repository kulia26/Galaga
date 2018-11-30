#ifndef SHOT_H
#define SHOT_H
#include "gameobject.h"

class Shot : public GameObject
{
public:
  Shot(QRect rect);
  void move(Direction direction) override;
};

#endif // SHOT_H
