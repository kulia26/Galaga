#include "enemy.h"
#include "animated.h"
#include <cmath>
#include <iostream>
#include <QPixmap>
#include <QRandomGenerator>
#include "moved.h"
Enemy::Enemy(Enemy::Type type, QPoint _start, QPoint _end,int _speed):GameObject(),Animated(GameObject::Type::Enemy)
{
  if(type == Type::Lobster){
      pixmap = QPixmap(":/images/images/LobsterSprites.png");
  }
  if(type == Type::Fly){
      pixmap = QPixmap(":/images/images/FlySprites.png");
  }
  if(type == Type::Wasp){
      pixmap = QPixmap(":/images/images/WaspSprites.png");
  }

  direction = Direction::none;
  speed = 1;
  makeFramesFromPixmap(&pixmap);
  rect  = QRect(_start.x(),_start.y(),frame->width()*3,frame->height()*3);

  tracks.push_back(new Moved(Moved::Path::Line,_start,_end,_speed));
  tracks.push_back(new Moved(Moved::Path::Stay,_end,_end,2));

  currentMoved  = tracks.first();
}

void Enemy::move()
{
  rect.moveTo(currentMoved->getNextPoint());
  if(currentMoved->getMovedPath()==Moved::Path::Line){
      animate(4, Animated::Type::MoveDownRight, GameObject::Type::Enemy);
    }
  if(currentMoved->getMovedPath()==Moved::Path::Stay){
      animate(8, Animated::Type::Stay, GameObject::Type::Enemy);
    }
  if(currentMoved->isEnded()){
      int i = tracks.indexOf(currentMoved);
      if((i+1)!=tracks.length()){
          currentMoved = tracks[i+1];
        }
    }
}
