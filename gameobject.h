#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QRect>
#include <QPixmap>

class GameObject
{
public:
  enum Direction { left, right, top, bottom, none };
  explicit GameObject();
  virtual ~GameObject();
  QRect getRect();
  QPixmap getPixmap();
  virtual void move();
  virtual void setSpeed(int speed);
protected:
  int speed;
  QRect rect;
  QPixmap pixmap;
};

#endif // GAMEOBJECT_H
