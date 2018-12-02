#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QRect>
#include <QPixmap>

class GameObject
{
public:
  enum Direction { left, right, top, bottom, none };
  GameObject();
  QRect getRect();
  QPixmap getPixmap();
  virtual void move();
  virtual ~GameObject();
protected:
  int speed;
  QRect rect;
  QPixmap pixmap;
};

#endif // GAMEOBJECT_H
