#ifndef SHOT_H
#define SHOT_H

#include "gameobject.h"
#include "moved.h"
#include "animated.h"

class Shot : public GameObject, public Moved, public Animated
{
public:
  explicit Shot(QRect rect);
  void move() override;
};

#endif // SHOT_H
