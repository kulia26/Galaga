#ifndef SHOT_H
#define SHOT_H

#include "gameobject.h"
#include "route.h"



class Shot : public GameObject
{
public:
  explicit Shot(QRect rect,Route::Path path);
  virtual ~Shot() override;
  void move() override;
};

#endif // SHOT_H
