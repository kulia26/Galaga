#include "physicalobject.h"

bool PhysicalObject::collide(const std::shared_ptr<PhysicalObject> object){
  bool res = QRect(this->rect & object->getRect()).size() != QSize(0,0);
  if(res){
     makeHurt(this,object);
    }
  return res;
}

bool PhysicalObject::collide(PhysicalObject* object){
  bool res = QRect(this->rect & object->getRect()).size() != QSize(0,0);
  if(res){
      makeHurt(this,object);
    }
  return res;
}

void PhysicalObject::makeHurt(PhysicalObject* object1, PhysicalObject* object2){
  if(object1->getType() == GameObject::Type::Shot || object2->getType() == GameObject::Type::Shot){
      object1->hurt();
      object2->hurt();
    }
  if(object1->getType() == GameObject::Type::Player && object2->getType() == GameObject::Type::Enemy){
      object1->hurt();
      object2->hurt();
    }
  if(object1->getType() == GameObject::Type::Enemy && object2->getType() == GameObject::Type::Player){
      object1->hurt();
      object2->hurt();
    }
}

void PhysicalObject::makeHurt(PhysicalObject* object1, const std::shared_ptr<PhysicalObject> object2){
  if(object1->getType() == GameObject::Type::Shot || object2->getType() == GameObject::Type::Shot){
      object1->hurt();
      object2->hurt();
    }
  if(object1->getType() == GameObject::Type::Player && object2->getType() == GameObject::Type::Enemy){
      object1->hurt();
      object2->hurt();
    }
  if(object1->getType() == GameObject::Type::Enemy && object2->getType() == GameObject::Type::Player){
      object1->hurt();
      object2->hurt();
    }
}

QRect PhysicalObject::getRect(){
  return rect;
}
