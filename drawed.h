#ifndef DRAWED_H
#define DRAWED_H

#include <QPainter>
#include <memory>
class Drawed
{
public:
  Drawed() = default;
  virtual ~Drawed() = default;
  virtual void draw(std::shared_ptr<QPainter> painter) = 0;
};

#endif // DRAWED_H
