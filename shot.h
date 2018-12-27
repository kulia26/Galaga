#ifndef SHOT_H
#define SHOT_H

#include "gameobject.h"
#include "physicalobject.h"
#include "route.h"

class Shot : public PhysicalObject
{
public:
  explicit Shot(QRect rect, Route::Path path);
  void move() override;
};

#endif // SHOT_H
