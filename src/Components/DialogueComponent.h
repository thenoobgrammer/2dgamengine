#ifndef INC_2DGAMEENGINE_DIALOGUE_COMPONENT_H
#define INC_2DGAMEENGINE_DIALOGUE_COMPONENT_H

#include <string>
#include <list>
#include <map>

#include "../tools/LinkedList.h"


struct DialogComponent {
    std::map<int, std::list<Node<std::string>>> dialogues;

    DialogComponent() = default;
};

#endif
