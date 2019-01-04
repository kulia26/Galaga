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

class GameObject: public Drawed, protected Routed
{
public:
  enum class Type{Player, Enemy, Explosion, Shot};

  GameObject() = default;
  virtual ~GameObject() = default;

  virtual void move();
  void draw(std::shared_ptr<QPainter> painter);
  void addRoute(Route::Path path, QPoint end);
  void addRoute(Route::Path path);

  void setPixmap(QString path);
  QPoint getPoint();
  Type getType();
  void  hurt();
  bool isAlive();

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
