#ifndef ROUTED_H
#define ROUTED_H
#include <QPoint>
#include <QVector>
#include "route.h"

class Routed
{
public:
  Routed() = default;
  virtual ~Routed() = default;

  virtual void addRoute(Route::Path path, QPoint end) = 0;
  virtual void addRoute(Route::Path path) = 0;
protected:
  Route* currentRoute;
  QVector<Route*> routes;
};

#endif // ROUTED_H
