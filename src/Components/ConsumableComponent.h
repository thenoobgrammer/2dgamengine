#ifndef INC_2DGAMEENGINE_CONSUMABLECOMPONENT_H
#define INC_2DGAMEENGINE_CONSUMABLECOMPONENT_H

struct ConsumableComponent {
    int giveBackHealth = 0;
    int giveBackMana = 0;
    int increasedArmor = 0;
    int increasedShield = 0;
    int increasedDamage = 0;
    int healthRegen = 0;
    int manaRegen = 0;

    ConsumableComponent(
        int giveBackHealth = 0,
        int giveBackMana = 0,
        int increasedArmor = 0,
        int increasedShield = 0,
        int increasedDamage = 0,
        int healthRegen = 0,
        int manaRegen = 0) {
        this->giveBackHealth = giveBackHealth;
        this->giveBackMana = giveBackMana;
        this->increasedArmor = increasedArmor;
        this->increasedShield = increasedShield;
        this->increasedDamage = increasedDamage;
        this->healthRegen = healthRegen;
        this->manaRegen = manaRegen;
    }
};


#endif