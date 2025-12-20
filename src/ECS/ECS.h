#ifndef INC_2DGAMEENGINE_ECS_H
#define INC_2DGAMEENGINE_ECS_H

#include <bitset>
#include <memory>
#include <set>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <deque>

#include "../Logger/Logger.h"

// We use a bitset (1s and 0s) to keep track of which components an entity has
// and also helps keep track which entities a system is interested in.
constexpr unsigned int MAX_COMPONENTS = 32;

typedef std::bitset<MAX_COMPONENTS> Signature;

/**********************************************************
 * The component structure :
 * Purely data, should contain an ID for accessibility
 **********************************************************/
struct IComponent {
    protected:
        static int nextId;
};

// Return a unique ID per component type
template<typename T>
class Component: public IComponent {
    public:
        static int GetId() {
            static auto id = nextId++;
            return id;
        }
};

/**********************************************************
 * The Entity structure :
 * Responsibility: Identify an object in the game
 **********************************************************/
class Entity {
    private:
        int id;
    public:
        Entity(int id) : id(id) {};
        Entity(const Entity& entity) = default;
        int GetId() const;
        void Kill();

        // Operation overloading which means dictates what these operators do for the entity class
        Entity& operator = (const Entity& _other) = default;
        bool operator == (const Entity& _other) const { return id == _other.id; };
        bool operator != (const Entity& _other) const { return id != _other.id; };
        bool operator > (const Entity& _other) const { return id > _other.id; };
        bool operator < (const Entity& _other) const { return id < _other.id; };

        template <typename TComponent, typename ...TArgs> void AddComponent(TArgs&& ...args);
        template <typename TComponent> void RemoveComponent();
        template <typename TComponent> bool HasComponent() const;
        template <typename TComponent> TComponent& GetComponent() const;

        // Hold a pointer to the owner/parent registry
        class Registry* registry; // Because registry is delcared later in the header file.
};


/**********************************************************
 * The System structure :
 * Responsibility: Set of logical instructions that allows
 * components to interact with each other
 **********************************************************/
class System {
    private:
        Signature componentSignature;
        std::vector<Entity> entities;

    public:
        System() = default;
        ~System() = default;

        void AddEntityToSystem(Entity entity);
        void RemoveEntityFromSystem(Entity entity);
        std::vector<Entity> GetSystemEntities() const;
        const Signature& GetComponentSignature() const;

        template<typename T> void RequireComponent();
};

/**********************************************************
 * The Pool class:
 * Responsibility: Wrapped list that takes a generic type
 **********************************************************/
class IPool {
    public:
        virtual ~IPool() = default;
};

template <typename T>
class Pool: public IPool {
    private:
        std::vector<T> pool;
    public:
        Pool(int size = 100) {
            pool.resize(size);
        }
        virtual ~Pool() = default;

        bool IsEmpty() const {
            return pool.size() == 0;
        }
        int GetSize() const {
            return pool.size();
        }
        void Resize(int size) {
            pool.resize(size);
        }
        void Clear() {
            pool.clear();
        }
        void Add(T object) {
            pool.push_back(object);
        }
        void Set(int index, T object) {
            pool[index] = object;
        }
        T& Get(int index) {
            return static_cast<T&>(pool[index]);
        }
        T& operator [](unsigned int index) {
            return pool[index];
        }
};

/**********************************************************
 * The Registry class:
 * Responsibility: Manages components, systems and entities -
 * provides accessor functions
 **********************************************************/
class Registry {
    private:
    int numEntities = 0;
    std::vector<std::shared_ptr<IPool>> componentPools;
    std::vector<Signature> entityComponentSignatures;

    std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

    std::set<Entity> entitiesToBeAdded;
    std::set<Entity> entitiesToBeKilled;

    std::deque<int> freeIds;

    public:
    Registry() = default;
    ~Registry() = default;

    Entity CreateEntity();

    void KillEntity(Entity entity);

    void Update();

    // Component management
    template <typename T, typename ...TArgs> void AddComponent(Entity entity, TArgs&& ...args);
    template <typename T> void RemoveComponent(Entity entity);
    template <typename T> bool HasComponent(Entity entity) const;
    template <typename T> T& GetComponent(Entity entity) const;

    // System management
    template <typename T, typename ...TArgs> void AddSystem(TArgs&& ...args);
    template <typename T> void RemoveSystem();
    template <typename T> bool HasSystem () const;
    template <typename T> T& GetSystem() const;

    // Checks the component signature of an entity and add the entity to the systems of interest
    void AddEntityToSystems(Entity entity);
    void RemoveEntityToSystems(Entity entity);
};

template<typename T>
void System::RequireComponent() {
    const auto componentId = Component<T>::GetId();
    componentSignature.set(componentId);
}

template <typename T, typename ...TArgs>
void Registry::AddSystem(TArgs&& ...args) {
    std::shared_ptr<T> newSystem = std::make_shared<T>(std::forward<TArgs>(args)...);
    systems.insert(std::make_pair(std::type_index(typeid(T)), newSystem));
}

template <typename T>
void Registry::RemoveSystem() {
    auto system = systems.find(std::type_index(typeid(T)));
    systems.erase(system);
}

template <typename T>
bool Registry::HasSystem () const {
    return systems.find(std::type_index(typeid(T))) != systems.end();
}

template <typename T>
T& Registry::GetSystem() const {
    auto system  = systems.find(std::type_index(typeid(T)));
    return *(std::static_pointer_cast<T>(system->second));
}

template<typename T, typename ...TArgs>
void Registry::AddComponent(Entity entity, TArgs&& ...args) {
    const int componentId = Component<T>::GetId();
    const int entityId = entity.GetId();

    if (componentId >= componentPools.size()) {
        componentPools.resize(componentId + 1, nullptr);
    }

    if (!componentPools[componentId]) {
        std::shared_ptr<Pool<T>> newcomponentPool = std::make_shared<Pool<T>>();
        componentPools[componentId] = newcomponentPool;
    }

    std::shared_ptr<Pool<T>> componentPool = std::static_pointer_cast<Pool<T>>(componentPools[componentId]);

    if (entityId >= componentPool->GetSize()) {
        componentPool->Resize(numEntities);
    }

    if (entityId >= entityComponentSignatures.size()) {
        entityComponentSignatures.resize(entityId + 1);
    }

    T newComponent(std::forward<TArgs>(args)...);
    componentPool->Set(entityId, newComponent);

    entityComponentSignatures[entityId].set(componentId);

    // Logger::Log("Added component " + std::to_string(componentId) + " to entity " + std::to_string(entityId));
}

template<typename T>
void Registry::RemoveComponent(Entity entity) {
    const auto componentId = Component<T>::GetId();
    const auto entityId = entity.GetId();
    entityComponentSignatures[entityId].set(componentId, false);

    // Logger::Log("Removed component " + std::to_string(componentId) + " from entity " + std::to_string(entityId));
}

template<typename T>
bool Registry::HasComponent(Entity entity) const {
    const auto componentId = Component<T>::GetId();
    const auto entityId = entity.GetId();
    return entityComponentSignatures[entityId].test(componentId);
}

template<typename T>
T& Registry::GetComponent(Entity entity) const {
    const auto componentId = Component<T>::GetId();
    const auto entityId = entity.GetId();
    auto componentPool = std::static_pointer_cast<Pool<T>>(componentPools[componentId]);
    return componentPool->Get(entityId);
}

template<typename TComponent, typename ...TArgs>
void Entity::AddComponent(TArgs&& ...args) {
    registry->AddComponent<TComponent>(*this, std::forward<TArgs>(args)...);
}

template<typename TComponent>
void Entity::RemoveComponent() {
    registry->RemoveComponent<TComponent>(*this);
}

template<typename TComponent>
bool Entity::HasComponent() const {
    return registry->HasComponent<TComponent>(*this);
}

template<typename TComponent>
TComponent& Entity::GetComponent() const {
    return registry->GetComponent<TComponent>(*this);
}

#endif