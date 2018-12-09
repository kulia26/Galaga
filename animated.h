#ifndef ANIMATED_H
#define ANIMATED_H

#include <QVector>
#include <QPixmap>
#include "gameobject.h"

class Animated
{
public:
  enum Type {MoveDownRight,Stay};
  explicit Animated(GameObject::Type gameObject);
  void makeFramesFromPixmap(QPixmap* pixmap);
  void animate(int delay, Type type, GameObject::Type gameObject);
  QPixmap getFrame();
  int getCurrentFrame();
protected:
  QPixmap* frame;
private:
  GameObject::Type gameObject;
  QVector<QPixmap*> frames;
  int framesCount;
  int delay;

};

#endif // ANIMATED_H
