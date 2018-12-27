#ifndef PHYSICALOBJECT_H
#define PHYSICALOBJECT_H

#include <memory>
#include <gameobject.h>

class PhysicalObject: public GameObject
{
public:
  PhysicalObject() = default;
  virtual ~PhysicalObject() = default;
  bool collide(const std::shared_ptr<PhysicalObject> object);
  bool collide(PhysicalObject* object);//*
  void makeHurt(PhysicalObject* object1, PhysicalObject* object2);
  void makeHurt(PhysicalObject* object1, const std::shared_ptr<PhysicalObject> object2);
  QRect getRect();
};

#endif // PHYSICALOBJECT_H
