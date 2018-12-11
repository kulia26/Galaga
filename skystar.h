#ifndef SKYSTAR_H
#define SKYSTAR_H

#include <QWidget>
#include "gameobject.h"
#include "moved.h"

class SkyStar : public GameObject, public Moved
{
public:
  SkyStar();
  void move() final override;
  int getShows();
  QColor getColor();
protected:
  int shows;
private:
  QColor color;
};

#endif // SKYSTAR_H
