#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QRect>
#include <QPixmap>
#include "route.h"
#include <memory>
#include <QPainter>
#include <memory>
#include "drawed.h"
#include "animated.h"
#include "routed.h"
#include "moved.h"

class GameObject: public Drawed, protected Routed, public Moved
{
public:
  enum class Type{Player, Enemy, Explosion, EnemyShot, PlayerShot};

  GameObject() = default;
  virtual ~GameObject() = default;

  void draw(std::shared_ptr<QPainter> painter);
  void addRoute(Route::Path path, QPoint end);
  void addRoute(Route::Path path);

  void setPixmap(QString path);
  QPoint getPoint();
  Type getType();
  void  hurt();
  bool isAlive();
  void moveRectTo(QPoint point);

  virtual void read(const QJsonObject &json);
  virtual void write(QJsonObject &json) const;

protected:
  double speed;
  GameObject::Type gameObjectType;
  QRect rect;
  QPixmap pixmap;
  int lives = 1;
private:
  QString imagePath;
};

#endif // GAMEOBJECT_H
