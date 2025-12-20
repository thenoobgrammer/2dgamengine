#ifndef INC_2DGAMEENGINE_NAMECOMPONENT_H
#define INC_2DGAMEENGINE_NAMECOMPONENT_H
#include <string>

struct NameComponent {
  std::string name;
  NameComponent(const std::string& n = "") : name(n) {}
};

#endif // INC_2DGAMEENGINE_NAMECOMPONENT_H
