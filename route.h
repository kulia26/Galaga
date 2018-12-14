#ifndef ROUTE_H
#define ROUTE_H

#include <QPoint>
#include <QJsonObject>

class Route
{
public:
  enum class Path {Line, Stay, Left, Right, Bottom, None, Lemniscate, Sin};

  explicit Route();
  explicit Route(Route::Path path, QPoint start, QPoint end);
  explicit Route(Route::Path path);
  explicit Route(Route::Path path, QPoint position);
  virtual ~Route();

  QPoint getNextPoint(double speed);
  QPoint getNextPoint(double speed,QPoint position);
  Route::Path getRoutePath();
  bool isEnded();

  void read(const QJsonObject &json);
  void write(QJsonObject &json) const;
protected:
  QPoint start;
  QPoint end; //!important
  Route::Path path;
private:
  QPoint position;
  double dx;
  double dy;
  double q;
  bool theEnd;
};

#endif // ROUTE_H
