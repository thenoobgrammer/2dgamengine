#ifndef INC_2DGAMEENGINE_EQUIPPABLECOMPONENT_H
#define INC_2DGAMEENGINE_EQUIPPABLECOMPONENT_H

struct EquippableComponent {
    enum EquippableSlot {
        MainHand,
        SecondaryHand
    };

    EquippableSlot hand;
    int attackBonus;
    int mageBonus;
    int armorBonus;

    EquippableComponent(EquippableSlot hand = MainHand, int attackBonus = 0, int mageBonus = 0, int armorBonus = 0) {
        this->hand = hand;
        this->attackBonus = attackBonus;
        this->mageBonus = mageBonus;
        this->armorBonus = armorBonus;
    }
};

#endif