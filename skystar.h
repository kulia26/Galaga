#ifndef SKYSTAR_H
#define SKYSTAR_H

#include <QWidget>
#include "gameobject.h"


class SkyStar : public GameObject
{
public:
  SkyStar();
  void move() final override;
  int getShows();
  QColor getColor();
  void draw(std::shared_ptr<QPainter> painter) final override;
private:
  QColor color;
};

#endif // SKYSTAR_H
