#ifndef INC_2DGAMEENGINE_FOLLOWMOUSEMOVEMENT_H
#define INC_2DGAMEENGINE_FOLLOWMOUSEMOVEMENT_H

#include "../Components/PlayerComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"
#include "../Events/MouseEvent.h"

class MouseTrackingSystem: public System {
  public:
  MouseTrackingSystem() {
    RequireComponent<PlayerComponent>();
    RequireComponent<TransformComponent>();
  }

  void Subscribe(std::unique_ptr<EventBus>& eventBus) {
    eventBus->Subscribe<MouseEvent>(this, &MouseTrackingSystem::onMouseMotion);
  }

  void onMouseMotion(MouseEvent& event) {
    auto& type = event.motionEvent.type;

    if (type == SDL_MOUSEMOTION) {
      for (auto& entity : GetSystemEntities()) {
        auto& transform = entity.GetComponent<TransformComponent>();
        auto& track = entity.GetComponent<MouseTrackComponent>();

        float deltaX = event.motionEvent.x - transform.position.x;
        float deltaY = event.motionEvent.y - transform.position.y;

        float angleRadians = std::atan2(deltaY, deltaX);
        float angleDegrees = angleRadians * 180.0f / M_PI;

        transform.rotation = angleDegrees + 90.0f;

        track.mouseX = event.motionEvent.x;
        track.mouseY = event.motionEvent.y;
        track.mouseAngle = angleDegrees;
      }
    }
  }

  void Update() {

  }
};

#endif
