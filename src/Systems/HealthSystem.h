#ifndef INC_2DGAMEENGINE_HEALTHSYSTEM_H
#define INC_2DGAMEENGINE_HEALTHSYSTEM_H

#include "../Components/LifeTimeComponent.h"
#include "../Components/TextComponent.h"
#include "../ECS/ECS.h"
#include "../Events/DamageEvent.h"

class HealthSystem: public System {
private:
  Registry* registry = nullptr;

public:
  HealthSystem() {
    RequireComponent<HealthComponent>();
  };
  ~HealthSystem() = default;

  void Subscribe(std::unique_ptr<EventBus>& eventBus, std::unique_ptr<Registry>& registry) {
    this->registry = registry.get();
    eventBus->Subscribe<DamageEvent>(this, &HealthSystem::onReceiveDamage);
  }

  void onReceiveDamage(DamageEvent& event) {
    auto& targetTransform = event.target.GetComponent<TransformComponent>();
    auto& targetHealth = event.target.GetComponent<HealthComponent>();
    targetHealth.currentHealth -= event.damage;

    Entity damageText = registry -> CreateEntity();
    damageText.AddComponent<TextComponent>("-" + std::to_string(event.damage), "damage-font", SDL_Color{ 190, 0, 0, 255 });
    damageText.AddComponent<LifeTimeComponent>(800);
    damageText.AddComponent<TransformComponent>(targetTransform.position, glm::vec2(1.0), 0.0);
    damageText.AddComponent<RigidBodyComponent>(glm::vec2(0.0, -20.0));
  }

  void Update() {
    for (auto& entity: GetSystemEntities()) {
      if (entity.HasComponent<HealthComponent>()) {
        auto& targetHealth = entity.GetComponent<HealthComponent>().currentHealth;
        if (targetHealth <= 0) {
          entity.Kill();
        }
      }
    }
  }
};

#endif
