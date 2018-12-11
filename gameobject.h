#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QRect>
#include <QPixmap>

class GameObject
{
public:
  enum Type{Player, Enemy, Explosion, Shot};
  explicit GameObject();
  explicit GameObject(QRect rect);
  QRect getRect();

  virtual ~GameObject();

  void read(const QJsonObject &json);
  void write(QJsonObject &json) const;
protected:
  QRect rect;
};

#endif // GAMEOBJECT_H
