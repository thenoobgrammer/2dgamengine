#ifndef INC_2DGAMEENGINE_HEALTHSYSTEM_H
#define INC_2DGAMEENGINE_HEALTHSYSTEM_H

#include "../ECS/ECS.h"
#include "../Events/DamageEvent.h"

class HealthSystem: public System {
public:
  HealthSystem() = default;
  ~HealthSystem() = default;

  void Subscribe(std::unique_ptr<EventBus>& eventBus) {
    eventBus->Subscribe<DamageEvent>(this, &HealthSystem::onReceiveDamage);
  }

  void Update() {

  }

  void onReceiveDamage(DamageEvent& event) {
    auto& targetName = event.target.GetComponent<NameComponent>().name;
    auto& target = event.target.GetComponent<HealthComponent>();
    target.currentHealth -=  event.damage;
    Logger::Log(targetName + " now has " + std::to_string(target.currentHealth) + " health remaining" + " | Damage done: " + std::to_string(event.damage));
    if (target.currentHealth <= 0) {
      event.target.Kill();
    }
  }
};

#endif // INC_2DGAMEENGINE_HEALTHSYSTEM_H
