#include "enemy.h"
#include "animated.h"
#include <cmath>
#include <iostream>
#include <QPixmap>
#include <QRandomGenerator>
#include "track.h"
Enemy::Enemy(Enemy::Type type, QPoint _start, QPoint _end,int _speed):GameObject(),Animated()
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
  makeFramesFromPixmap(&pixmap, GameObject::Type::Enemy);
  rect  = QRect(_start.x(),_start.y(),frame->width()*3,frame->height()*3);

  tracks.push_back(new Track(Track::Path::Line,_start,_end,_speed));
  tracks.push_back(new Track(Track::Path::Stay,_end,_end,2));

  currentTrack  = tracks.first();
}

void Enemy::move()
{
  rect.moveTo(currentTrack->getNextPoint());
  if(currentTrack->getTrackPath()==Track::Path::Line){
      animate(4, Animated::Type::MoveDownRight, GameObject::Type::Enemy);
    }
  if(currentTrack->getTrackPath()==Track::Path::Stay){
      animate(8, Animated::Type::Stay, GameObject::Type::Enemy);
    }
  if(currentTrack->isEnded()){
      int i = tracks.indexOf(currentTrack);
      if((i+1)!=tracks.length()){
          currentTrack = tracks[i+1];
        }
    }
}
