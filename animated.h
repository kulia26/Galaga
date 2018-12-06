#ifndef ANIMATED_H
#define ANIMATED_H

#include <QVector>
#include <QPixmap>


class Animated
{
public:
  enum Type {MoveLeft, MoveRight, MoveDown, MoveUp, Stay};
  enum GameObjectType{Player, Enemy, Explosion};
  Animated();
  void makeFramesFromPixmap(QPixmap* pixmap, GameObjectType gameObject);
  void animate(int delay, Type type, GameObjectType gameObject);
  QPixmap getFrame();
  int getFramesCount();
  QPixmap* frame;
  QVector<QPixmap*> frames;
  int framesCount;
  int delay;

};

#endif // ANIMATED_H
