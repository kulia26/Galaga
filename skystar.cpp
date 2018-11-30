#include "skystar.h"
#include <QRandomGenerator>

SkyStar::SkyStar()
{
  int size  = QRandomGenerator::global()->bounded(0,3);
  color = QColor(QRandomGenerator::global()->bounded(0,255),QRandomGenerator::global()->bounded(0,255),QRandomGenerator::global()->bounded(0,255),QRandomGenerator::global()->bounded(0,255));
  rect = QRect(QRandomGenerator::global()->bounded(0,600),QRandomGenerator::global()->bounded(0,800),size,size);
  shows = QRandomGenerator::global()->bounded(10,30);
}

void SkyStar::move(GameObject::Direction direction)
{
   rect = QRect(rect.left(),rect.top()+3,rect.width(),rect.height());
   shows++;
}

