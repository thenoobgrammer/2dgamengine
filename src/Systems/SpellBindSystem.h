#ifndef INC_2DGAMEENGINE_SPELLBINDSYSTEM_H
#define INC_2DGAMEENGINE_SPELLBINDSYSTEM_H
#include "../ECS/ECS.h"

class SpellBindSystem: public System {
    enum ElementalOrbs {
        None,
        Fire,
        Dark,
        Light,
        Lighting,
        Wind,
        Earth
    };

    struct Spell {
        Spell(std::string name = "", ElementalOrbs orb1 = {}, ElementalOrbs orb2 = {}, float baseDamage = 20.0);
        std::string name;
        ElementalOrbs orb1;
        ElementalOrbs orb2;
        float baseDamage;
    };

    Spell SpellCombinations[36] = {
        Spell("Inferno", Fire, Fire),
        Spell("Firestorm", Fire, Wind),
        Spell("Magma", Fire, Earth),
        Spell("Plasma", Fire, Lighting),
        Spell("Solar Flare", Fire, Light),
        Spell("HellFire", Fire, Dark),
    };
    private:
        Spell availableSpells [6] = {};
    public:
        SpellBindSystem() {
            // TODO:
            //  Get the player equipment
            //  1. Find the entity(ies) orb(s)
            //  2. Get the value of each orb and give a list of available spells
            //  3. Set availableSpells to whichever orb they have combined
        }
};

#endif