#include "physicalobject.h"

bool PhysicalObject::collide(const std::shared_ptr<PhysicalObject> object){
  return QRect(this->rect & object->getRect()).size() != QSize(0,0);
}

bool PhysicalObject::collide(PhysicalObject* object){
  return QRect(this->rect & object->getRect()).size() != QSize(0,0);
}

QRect PhysicalObject::getRect(){
  return rect;
}
