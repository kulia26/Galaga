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
  void draw(std::shared_ptr<QPainter> painter) final override;
};

#endif // SHOT_H
