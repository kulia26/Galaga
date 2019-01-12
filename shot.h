#ifndef SHOT_H
#define SHOT_H

#include "gameobject.h"
#include "physicalobject.h"
#include "route.h"

class Shot : public PhysicalObject
{
public:
  explicit Shot(QRect rect, GameObject::Type owner);
  explicit Shot() = default;
  void move() override;
  void reuse(QPoint point);
};

#endif // SHOT_H
