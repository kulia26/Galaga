#ifndef SHOT_H
#define SHOT_H

#include "gameobject.h"



class Shot : public GameObject
{
public:
  explicit Shot(QRect rect);
  void move() override;
};

#endif // SHOT_H
