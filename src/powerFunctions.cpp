#include "powerFunctions.h"
#include <iostream>

void powerFunctions::spike (Entity &user, int turnCounter) {
    int FIRST_TURN = 1;
}

void powerFunctions::grow_strength (Entity &user, int turnCounter) {
    user.attack++;
    std::cout << user.name << "'s strength grew!" << std::endl;
}

void powerFunctions::no_guard (Entity &user, int turnCounter) {
    if (turnCounter == 1) { user.attack += 3; }

    user.guard = -3;
}

void powerFunctions::regenerate (Entity &user, int turnCounter) {
    user.health += 2;

    if (user.health > user.maxHealth) {
        user.health = user.maxHealth;

    }

}

void powerFunctions::wither (Entity &user, int turnCounter) {
    user.health -= 2;

    user.guard = -1 * turnCounter + 1;

}

void powerFunctions::metal_body (Entity &user, int turnCounter) {
    user.guard += 2;

}

void powerFunctions::strength_boost (Entity &user, int turnCounter) {
    if (turnCounter == 1) { user.attack += 1; }

}