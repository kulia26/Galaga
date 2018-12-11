#include "skystar.h"
#include "moved.h"
#include <QRandomGenerator>

SkyStar::SkyStar():GameObject (), Moved()
{
  int size  = QRandomGenerator::global()->bounded(1,3);
  speed = QRandomGenerator::global()->bounded(1,5);
  color = QColor(QRandomGenerator::global()->bounded(0,255),QRandomGenerator::global()->bounded(0,255),QRandomGenerator::global()->bounded(0,255),QRandomGenerator::global()->bounded(0,255));
  rect = QRect(QRandomGenerator::global()->bounded(0,600),QRandomGenerator::global()->bounded(-100,700),size,size);
  if(rect.top() < 0){
      shows = -10;
    }
  else{
      shows = 0;
    }
  shows = shows + QRandomGenerator::global()->bounded(-15,10);
}


void SkyStar::move()
{
   rect = QRect(rect.left(),rect.top()+speed,rect.width(),rect.height());
   shows++;
}

int SkyStar::getShows()
{
   return shows;
}

QColor SkyStar::getColor()
{
   return color;
}

