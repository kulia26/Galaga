#include "skystar.h"
#include <QRandomGenerator>

SkyStar::SkyStar()
{
  setSpeed(QRandomGenerator::global()->bounded(1,6));
  int size  = QRandomGenerator::global()->bounded(0,3);
  color = QColor(QRandomGenerator::global()->bounded(0,255),QRandomGenerator::global()->bounded(0,255),QRandomGenerator::global()->bounded(0,255),QRandomGenerator::global()->bounded(0,255));
  rect = QRect(QRandomGenerator::global()->bounded(0,600),QRandomGenerator::global()->bounded(0,800),size,size);
  shows = QRandomGenerator::global()->bounded(0,20);
}

void SkyStar::move()
{
   rect = QRect(rect.left(),rect.top()+speed,rect.width(),rect.height());
   shows++;
}

