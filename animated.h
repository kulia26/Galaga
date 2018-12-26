#ifndef ANIMATED_H
#define ANIMATED_H

class Animated
{
public:
  enum class Animation {MoveDownRight,Stay};
  Animated() = default;
  virtual ~Animated() = default;
  virtual void makeFramesFromPixmap() = 0;
  virtual void animate(Animation type)= 0;
};

#endif // ANIMATED_H
