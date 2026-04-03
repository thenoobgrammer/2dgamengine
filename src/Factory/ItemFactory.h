#ifndef INC_2DGAMEENGINE_ITEMFACTORY_H
#define INC_2DGAMEENGINE_ITEMFACTORY_H
#include "../Components/elements/Item.h"
#include "../ECS/ECS.h"
#include "glm/glm.hpp"


class ItemFactory {
    public:
    Registry *registry = nullptr;

    explicit ItemFactory(const std::unique_ptr<Registry> &registry);
    virtual ~ItemFactory() = default;
    void Spawn(const Item& item, glm::vec2 position, int count) const;
};


#endif
