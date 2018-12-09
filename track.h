#ifndef TRACK_H
#define TRACK_H

#include <QPoint>

class Track
{
public:
  enum Path {Circle, HalfCircle, Line, Stay};
  Track();
  explicit Track(Path path, QPoint begin, QPoint end, int speed);
  QPoint getNextPoint();
  Path getTrackPath();
  bool isEnded();
private:
  QPoint begin;
  QPoint end;
  QPoint position;
  double dx;
  double dy;
  double phi;
  double speed;
  Path path;
  bool theEnd;
};

#endif // TRACK_H
