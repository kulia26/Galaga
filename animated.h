#ifndef ANIMATED_H
#define ANIMATED_H

#include <QPixmap>
class Animated
{
public:
  enum class Animation {MoveDownRight,Stay};
  Animated() = default;
  virtual ~Animated() = default;
  virtual void makeFramesFromPixmap() = 0;
  virtual void animate(Animation type)= 0;

protected:
  QPixmap* frame;
  QVector<QPixmap*> frames;
  int framesCount;
};

#endif // ANIMATED_H
