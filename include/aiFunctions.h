#ifndef AIFUNCTIONS_H
#define AIFUNCTIONS_H
#include "Entity.h"
#include "Skill.h"

namespace aiFunctions
{

    void slime (Entity &user, Entity &target, int turnCounter);

    void blue_slime (Entity &user, Entity &target, int turnCounter);

    void rock (Entity &user, Entity &target, int turnCounter);

    void spore_flower (Entity &user, Entity &target, int turnCounter);

    void shieldKnight (Entity &user, Entity &target, int turnCounter);

    void vampire (Entity &user, Entity &target, int turnCounter);

    void brute (Entity &user, Entity &target, int turnCounter);

    void wither (Entity &user, Entity &target, int turnCounter);
};


#endif // AIFUNCTIONS_H