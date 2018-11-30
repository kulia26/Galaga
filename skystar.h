#ifndef SKYSTAR_H
#define SKYSTAR_H

#include <QWidget>
#include "gameobject.h"

class SkyStar : public GameObject
{
public:
  QColor color;
  int shows;
  SkyStar();
  void move(Direction direction) override;
};

#endif // SKYSTAR_H
