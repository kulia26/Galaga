#include "moved.h"
#include <cmath>
#include <QRect>


Moved::Moved(Path _path, QPoint _begin, QPoint _end, int _speed)
{
  path =_path;
  begin = _begin;
  end = _end;
  speed = _speed;
  position = _begin;
  theEnd = false;

}

QPoint Moved::getNextPoint(){
  if((QRect(position,end).height()<2 || QRect(position,end).width()<2) && path == Path::Line){
      position = end;
      theEnd = true;
    }else{
      if(path== Path::Line){
          dx = (end.x() - begin.x())/speed;
          dy = (end.y() - begin.y())/speed;
        }
      if(path== Path::Stay){
          if(position.x()-end.x() <= -4){
              dx = dx +speed/3;
            }else{
                  dx = dx - speed/3;
            }
        }
      position = QPoint(static_cast<int>(position.x()+dx),static_cast<int>(position.y()+dy));
    }
  return position;
}


bool Moved::isEnded(){
  return theEnd;
}

Moved::Path Moved::getMovedPath(){
  return path;
}

