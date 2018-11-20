#include "skystar.h"
#include <QRandomGenerator>

SkyStar::SkyStar()
{
  int size  = QRandomGenerator::global()->bounded(0,4);
  color = QColor(QRandomGenerator::global()->bounded(0,255),QRandomGenerator::global()->bounded(0,255),QRandomGenerator::global()->bounded(0,255),QRandomGenerator::global()->bounded(0,255));
  star = QRect(QRandomGenerator::global()->bounded(0,800),QRandomGenerator::global()->bounded(0,600),size,size);
}
