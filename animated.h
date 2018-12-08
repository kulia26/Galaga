#ifndef ANIMATED_H
#define ANIMATED_H

#include <QVector>
#include <QPixmap>
#include "gameobject.h"

class Animated
{
public:
  enum Type {MoveLeft, MoveRight, MoveDown, MoveUp, Stay};
  Animated();
  void makeFramesFromPixmap(QPixmap* pixmap, GameObject::Type gameObject);
  void animate(int delay, Type type, GameObject::Type gameObject);
  QPixmap getFrame();
  int getCurrentFrame();
  QPixmap* frame;
  QVector<QPixmap*> frames;
  int framesCount;
  int delay;

};

#endif // ANIMATED_H
