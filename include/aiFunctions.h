#ifndef AIFUNCTIONS_H
#define AIFUNCTIONS_H
#include "Entity.h"
#include "Skill.h"

namespace aiFunctions
{

    void slime (Entity &user, Entity &target, int turnCounter);

    void wisp (Entity &user, Entity &target, int turnCounter);

    void blue_slime (Entity &user, Entity &target, int turnCounter);

    void artifact (Entity &user, Entity &target, int turnCounter);

    void rock (Entity &user, Entity &target, int turnCounter);

    void shieldKnight (Entity &user, Entity &target, int turnCounter);

    void vampire (Entity &user, Entity &target, int turnCounter);

    void brute (Entity &user, Entity &target, int turnCounter);

    void bowman (Entity &user, Entity &target, int turnCounter);

    void crusader (Entity &user, Entity &target, int turnCounter);

    void minotaur (Entity &user, Entity &target, int turnCounter);

    void werewolf (Entity &user, Entity &target, int turnCounter);

    void shadow (Entity &user, Entity &target, int turnCounter);

    void beholder (Entity &user, Entity &target, int turnCounter);

    void thief (Entity &user, Entity &target, int turnCounter);

    void spirit (Entity &user, Entity &target, int turnCounter);

    void bramble (Entity &user, Entity &target, int turnCounter);

    void herbalist (Entity &user, Entity &target, int turnCounter);

    void wither (Entity &user, Entity &target, int turnCounter);

    void dragon (Entity &user, Entity &target, int turnCounter);

    void carl (Entity &user, Entity &target, int turnCounter);
};


#endif // AIFUNCTIONS_H
