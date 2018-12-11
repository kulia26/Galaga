#ifndef ANIMATED_H
#define ANIMATED_H

#include <QVector>
#include <QPixmap>
#include "gameobject.h"

class Animated
{
public:
  enum Type {MoveDownRight,Stay};
  explicit Animated();
  explicit Animated(QPixmap pixmap);
  explicit Animated(GameObject::Type gameObject);
  explicit Animated(GameObject::Type gameObject, QPixmap pixmap);
  void makeFramesFromPixmap(QPixmap* pixmap);
  void animate(int delay, Type type, GameObject::Type gameObject);
  //сделать двойное использование вместо функции конструктор как в мувд
  QPixmap getFrame();
  int getCurrentFrame();
  QPixmap getPixmap();
  void setPixmap(QString path);

  void read(const QJsonObject &json);
  void write(QJsonObject &json) const;
protected:
  QPixmap* frame;
  QPixmap pixmap;
private:
  GameObject::Type gameObject;
  QVector<QPixmap*> frames;
  QString imagePath;
  int framesCount;
  int delay;


};

#endif // ANIMATED_H
