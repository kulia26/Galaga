#ifndef MOVED_H
#define MOVED_H

#include <QPoint>

class Moved
{
public:
  enum Path {Line, Stay, Left, Right, Bottom};
  explicit Moved(Path path, QPoint begin, QPoint end, int speed);
  QPoint getNextPoint();
  Path getMovedPath();
  bool isEnded();
private:
  QPoint begin;
  QPoint end;
  QPoint position;
  double dx;
  double dy;
  double speed;
  Path path;
  bool theEnd;
};

#endif // MOVED_H
