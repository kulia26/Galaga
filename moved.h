#ifndef MOVED_H
#define MOVED_H

#include <QPoint>
#include <QJsonObject>

class Moved
{
public:
  enum Path {Line, Stay, Left, Right, Bottom, None};
  explicit Moved(Path path, QPoint start, QPoint end, int speed);
  explicit Moved(Path path, int speed);
  explicit Moved();
  virtual ~Moved();
  QPoint getNextPoint();
  Path getMovedPath();
  bool isEnded();
  virtual void move();
  void read(const QJsonObject &json);
  void write(QJsonObject &json) const;
protected:
  QPoint start;
  QPoint end;
  int speed;
  Path path;
private:
  QPoint position;
  double dx;
  double dy;
  bool theEnd;
};

#endif // MOVED_H
