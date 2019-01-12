#include "physicalobject.h"

bool PhysicalObject::collide(const std::shared_ptr<PhysicalObject> object){
  bool res = QRect(this->rect & object->getRect()).size() != QSize(0,0);
  return res;
}

bool PhysicalObject::collide(PhysicalObject* object){
  bool res = QRect(this->rect & object->getRect()).size() != QSize(0,0);
  return res;
}

QRect PhysicalObject::getRect(){
  return rect;
}
