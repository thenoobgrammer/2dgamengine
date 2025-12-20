#ifndef INC_2DGAMEENGINE_HEALTHCOMPONENT_H
#define INC_2DGAMEENGINE_HEALTHCOMPONENT_H

struct HealthComponent {
    float maxHealth;
    float currentHealth;

    HealthComponent(float maxHealth = 0.0f, float currentHealth = -1) {
      this->maxHealth = maxHealth;
      this->currentHealth = currentHealth < 0 ? maxHealth : currentHealth;
    }
};

#endif // INC_2DGAMEENGINE_HEALTHCOMPONENT_H
