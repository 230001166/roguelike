#include "Game.h"
#include "Status.h"
#include "aiFunctions.h"
#include "powerFunctions.h"
#include "skillFunctions.h"
#include "utilityFunctions.h"
#include <iostream>
#include <time.h>

Game::~Game()
{
    //dtor
}

void Game::battle (Entity &player, Entity &enemy) {
    int turnCounter = 1;

    while (player.health > 0 && enemy.health > 0) {
        std::cout << "TURN " << turnCounter << std::endl;

        for (unsigned int i = 0; i < player.powers.size (); i++) { player.powers [i]->use (player, turnCounter); }

        displayPlayerInformation (player, enemy);

        int choice = -1; bool looping = true;

        while (looping) {
            choice = utilityFunctions::getIntegerInput ();

            if (choice >= 0 && choice < 3) { looping = false; }

        }

        player.skillset [choice]->use (player, enemy);

        enemy.guard = 0;

        if (enemy.health > 0) {
            for (unsigned int i = 0; i < enemy.powers.size (); i++) { enemy.powers [i]->use (enemy, turnCounter); }

            enemy.ai (enemy, player, turnCounter);
        }

        turnCounter++; player.guard = 0;

    }

    if (player.health > 0) {

        std::cout << "You won!" << std::endl;

        replaceSkill (player, enemy.rewardSkill);
        player.gold += enemy.gold;
        player.maxHealth++; player.health++;
        player.attack = 0;

    }

}

void Game::displayPlayerInformation (Entity &player, Entity &enemy) {
    std::cout << player.name << " vs. " << enemy.name << std::endl;
    std::cout << "HP " << player.health << " / " << player.maxHealth << " vs. " << enemy.health << " / " << enemy.maxHealth << std::endl;
    std::cout << "Player Powers: ";
    for (unsigned int i = 0; i < player.powers.size (); i++) {
        std::cout << player.powers [i]->name;

        if (i < player.powers.size () - 1) { std::cout << ", "; }
    }
    std::cout << "\nEnemy Powers: ";
    for (unsigned int i = 0; i < enemy.powers.size (); i++) {
        std::cout << enemy.powers [i]->name;

        if (i < enemy.powers.size () - 1) { std::cout << ", "; }
    }

    std::cout << "\nPlayer Skills:" << std::endl;

    for (int i = 0; i < 3; i++) {
        std::cout << "[" << i << "] - " << player.skillset [i]->name << std::endl;
    }

}

void Game::initializeSkills () {

    Skill doNothing; doNothing.name = "Do Nothing"; doNothing.use = skillFunctions::do_nothing; gameSkills.push_back (doNothing);

    Skill attack; attack.name = "Attack"; attack.use = skillFunctions::attack; gameSkills.push_back (attack);

    Skill dagger; dagger.name = "Dagger"; dagger.use = skillFunctions::dagger; gameSkills.push_back (dagger);

    Skill defend; defend.name = "Defend"; defend.use = skillFunctions::defend; gameSkills.push_back (defend);

    Skill leech; leech.name = "Leech"; leech.use = skillFunctions::leech; gameSkills.push_back (leech);

    Skill last_resort; last_resort.name = "Last Resort"; last_resort.use = skillFunctions::last_resort; gameSkills.push_back (last_resort);

    Skill restore; restore.name = "Restore"; restore.use = skillFunctions::restore; gameSkills.push_back (restore);

    Skill guardBreak; guardBreak.name = "Guard Break"; guardBreak.use = skillFunctions::guard_break; gameSkills.push_back (guardBreak);

    Skill arrow; arrow.name = "Arrow"; arrow.use = skillFunctions::arrow; gameSkills.push_back (arrow);

}

void Game::initializePowers () {

    Power growStrength; growStrength.name = "Grow"; growStrength.use = powerFunctions::grow_strength; gamePowers.push_back (growStrength);

    Power noGuard; noGuard.name = "No Guard"; noGuard.use = powerFunctions::no_guard; gamePowers.push_back (noGuard);

    Power regen; regen.name = "Regenerate"; regen.use = powerFunctions::regenerate; gamePowers.push_back (regen);

    Power wither; wither.name = "Wither"; wither.use = powerFunctions::wither; gamePowers.push_back (wither);

    Power metalBody; metalBody.name = "Metal Body"; metalBody.use = powerFunctions::metal_body; gamePowers.push_back (metalBody);

    Power strengthBoost; strengthBoost.name = "Strength Boost"; strengthBoost.use = powerFunctions::strength_boost; gamePowers.push_back (strengthBoost);

    Power spike; spike.name = "Thorns"; spike.use = powerFunctions::spike; gamePowers.push_back (spike);

}

Entity Game::returnEntityFromName (std::string name) {
    Entity entity;
    srand (time (NULL));

    if (name == "Slime") {
        entity.health = 27;
        entity.maxHealth = 27;
        entity.name = "Slime";

        entity.gold = utilityFunctions::random (8, 24);

        entity.skillset [0] = &gameSkills [1];
        entity.skillset [1] = &gameSkills [0];

        entity.rewardSkill = &gameSkills [1];

        entity.ai = aiFunctions::slime;
    }
    if (name == "Blue Slime") {
        entity.health = 17;
        entity.maxHealth = 17;
        entity.name = "Blue Slime";

        entity.gold = utilityFunctions::random (8, 24);

        entity.skillset [0] = &gameSkills [1];
        entity.skillset [1] = &gameSkills [0];

        entity.rewardSkill = &gameSkills [1];

        entity.powers.push_back (&gamePowers [2]);
        entity.ai = aiFunctions::blue_slime;
    }
    if (name == "Rock") {
        entity.health = 1;
        entity.maxHealth = 1;
        entity.name = "Rock";

        entity.gold = utilityFunctions::random (1, 3);

        entity.skillset [0] = &gameSkills [0];

        entity.rewardSkill = &gameSkills [0];

        entity.ai = aiFunctions::rock;
    }
    if (name == "Thornbush") {
        entity.health = 14;
        entity.maxHealth = 14;
        entity.name = "Thornbush";

        entity.gold = utilityFunctions::random (22, 31);

        entity.skillset [0] = &gameSkills [2];
        entity.skillset [1] = &gameSkills [1];

        entity.rewardSkill = &gameSkills [2];

        entity.powers.push_back (&gamePowers [6]);
        entity.ai = aiFunctions::spore_flower;
    }
    if (name == "Shield Warrior") {
        entity.health = 11;
        entity.maxHealth = 11;
        entity.name = "Shield Warrior";

        entity.gold = utilityFunctions::random (11, 28);

        entity.skillset [0] = &gameSkills [1];
        entity.skillset [1] = &gameSkills [3];
        entity.skillset [2] = &gameSkills [0];

        entity.rewardSkill = &gameSkills [3];

        entity.ai = aiFunctions::shieldKnight;
    }
    if (name == "Vampire") {
        entity.health = 12;
        entity.maxHealth = 12;
        entity.name = "Vampire";

        entity.gold = utilityFunctions::random (16, 39);

        entity.skillset [0] = &gameSkills [4];
        entity.skillset [1] = &gameSkills [3];

        entity.rewardSkill = &gameSkills [4];

        entity.ai = aiFunctions::vampire;
    }
    if (name == "Brute") {
        entity.health = 26;
        entity.maxHealth = 26;
        entity.name = "Brute";

        entity.gold = utilityFunctions::random (23, 32);

        entity.skillset [0] = &gameSkills [1];
        entity.skillset [1] = &gameSkills [0];

        entity.rewardSkill = &gameSkills [1];

        entity.powers.push_back (&gamePowers [1]);
        entity.ai = aiFunctions::brute;
    }
    if (name == "Bowman") {
        entity.health = 19;
        entity.maxHealth = 19;
        entity.name = "Bowman";

        entity.gold = utilityFunctions::random (16, 22);

        entity.skillset [0] = &gameSkills [8];
        entity.skillset [1] = &gameSkills [3];

        entity.rewardSkill = &gameSkills [8];

        entity.ai = aiFunctions::bowman;
    }
    if (name == "Artifact") {
        entity.health = 36;
        entity.maxHealth = 36;
        entity.name = "Artifact";

        entity.gold = utilityFunctions::random (5, 28);

        entity.skillset [0] = &gameSkills [1];
        entity.skillset [1] = &gameSkills [3];
        entity.skillset [2] = &gameSkills [7];

        entity.rewardSkill = &gameSkills [3];

        entity.powers.push_back (&gamePowers [4]);
        entity.ai = aiFunctions::artifact;
    }
    if (name == "Wither") {
        entity.health = 60;
        entity.maxHealth = 60;
        entity.name = "Wither";

        entity.gold = utilityFunctions::random (80, 124);

        entity.skillset [0] = &gameSkills [4];
        entity.skillset [1] = &gameSkills [5];
        entity.skillset [2] = &gameSkills [0];


        entity.rewardSkill = &gameSkills [1];

        entity.powers.push_back (&gamePowers [3]);
        entity.powers.push_back (&gamePowers [1]);
        entity.ai = aiFunctions::wither;
    }

    return entity;

}

void Game::replaceSkill (Entity &player, Skill *rewardSkill) {

    std::cout << "Reward Skill: " << rewardSkill->name << "\nChoose a skill to replace." << std::endl;

    bool looping = true; int choice = -1;

    while (looping) {
        for (int i = 0; i < 3; i++) {
            std::cout << "[" << i << "] - " << player.skillset [i]->name << std::endl;

        }

        choice = utilityFunctions::getIntegerInput ();

        if (choice >= 0 && choice < 3) { looping = false; }
    }

    player.skillset [choice] = rewardSkill;

}

void Game::generateMap (int seed) {
    for (int i = 0; i < 10; i++) {
        dungeon [i] = generateFloor (seed, i + 1);

    }
}

Floor Game::generateFloor (int seed, int floorNumber) {

    Floor floor;
    Room startingPoint; startingPoint.roomType = "start";

    floor.floorMap [0] = startingPoint;

    for (int i = 0; i < 12; i++) { srand (seed*i);

        floor.floorMap [1+i] = generateRoom (floorNumber);

    }

    Room midBoss; midBoss.roomType = "enemy"; midBoss.entityInRoom = returnEntityFromName ("Bowman");

    floor.floorMap [13] = midBoss;

    for (int i = 0; i < 12; i++) {  srand (seed*i);


        floor.floorMap [14+i] = generateRoom (floorNumber);

    }

    Room boss; boss.roomType = "enemy"; boss.entityInRoom = returnEntityFromName ("Blue Slime");

    floor.floorMap [26] = boss;

    int index = utilityFunctions::random (0, gamePowers.size () - 1);
    floor.powerReward = gamePowers [index];

    return floor;
}

Room Game::generateRoom (int floorNumber) {
    int random = utilityFunctions::random (1, 100); Room room;

    if (random >= 40) {
        std::vector <std::string> enemyNames;

        switch (floorNumber) {
            case 1: {
                enemyNames.push_back ("Rock");
                enemyNames.push_back ("Slime");
                enemyNames.push_back ("Shield Warrior");
                enemyNames.push_back ("Vampire");

            } break;
            case 2: {
                enemyNames.push_back ("Vampire");
                enemyNames.push_back ("Thornbush");
                enemyNames.push_back ("Rock");

            } break;
            case 3: {
                enemyNames.push_back ("Vampire");
                enemyNames.push_back ("Thornbush");
                enemyNames.push_back ("Rock");
                enemyNames.push_back ("Brute");
                enemyNames.push_back ("Blue Slime");

            } break;
            case 4: {
                enemyNames.push_back ("Rock");
                enemyNames.push_back ("Brute");
                enemyNames.push_back ("Blue Slime");

            } break;
            case 5: {
                enemyNames.push_back ("Rock");
                enemyNames.push_back ("Brute");
                enemyNames.push_back ("Blue Slime");

            } break;
            case 6: {
                enemyNames.push_back ("Rock");
                enemyNames.push_back ("Brute");
                enemyNames.push_back ("Blue Slime");

            } break;
            case 7: {
                enemyNames.push_back ("Rock");

            } break;
            case 8: {
                enemyNames.push_back ("Rock");

            } break;
            case 9: {
                enemyNames.push_back ("Rock");

            } break;
            case 10: {
                enemyNames.push_back ("Rock");

            } break;
        }

        int index = utilityFunctions::random (0, enemyNames.size () - 1);

        room.entityInRoom = returnEntityFromName (enemyNames [index]); room.roomType = "enemy";

    } else if (random >= 20) {
        int index = utilityFunctions::random (0, gameSkills.size () - 1);
        room.skillReward = gameSkills [index];
        room.priceOfHeal = utilityFunctions::random (24, 108);
        room.priceOfSkill = utilityFunctions::random (24, 108);
        room.roomType = "shop";
    } else if (random >= 10) {
        int index = utilityFunctions::random (0, gameSkills.size () - 1);

        room.skillReward = gameSkills [index]; room.roomType = "skillreward";
    } else {
        int goldReward = utilityFunctions::random (1, 100); room.goldReward = goldReward; room.roomType = "goldreward";
    }

    return room;
}

void Game::displayRoomChoices (int roomIndex) {
    const int START = 0, MIDBOSS = 13, BOSS = 26;
    if (roomIndex == START) {
        std::cout << "[1] " << dungeon [floor - 1].floorMap [1].roomType << std::endl;
        std::cout << "[2] " << dungeon [floor - 1].floorMap [2].roomType << std::endl;
        std::cout << "[3] " << dungeon [floor - 1].floorMap [3].roomType << std::endl;
    } else if (roomIndex >= 10 && roomIndex <= 12) {
        std::cout << "[1] Midboss" << std::endl;
    } else if (roomIndex == MIDBOSS) {
        std::cout << "[1] " << dungeon [floor - 1].floorMap [14].roomType << std::endl;
        std::cout << "[2] " << dungeon [floor - 1].floorMap [15].roomType << std::endl;
        std::cout << "[3] " << dungeon [floor - 1].floorMap [16].roomType << std::endl;
    } else if (roomIndex >= 23 && roomIndex <= 25) {
        std::cout << "[1] Floor boss" << std::endl;
    } else if (roomIndex < BOSS) {
        std::cout << "[1] " << dungeon [floor - 1].floorMap [roomIndex+3].roomType << std::endl;
    }
}

void Game::displayPaths () {

    std::cout << "Path 1: ";
    for (unsigned int i = 0; i < 4; i++) { std::cout << dungeon [floor - 1].floorMap [1 + i*3].roomType;
        if (dungeon [floor - 1].floorMap [1 + i*3].roomType == "enemy") {
            std::cout << " - " << dungeon [floor - 1].floorMap [1 + i*3].entityInRoom.name;
        }
        std::cout << ", ";
    }
    std::cout << dungeon [floor - 1].floorMap [13].roomType << ", ";
    for (unsigned int i = 0; i < 4; i++) { std::cout << dungeon [floor - 1].floorMap [14 + i*3].roomType;
        if (dungeon [floor - 1].floorMap [14 + i*3].roomType == "enemy") {
            std::cout << " - " << dungeon [floor - 1].floorMap [14 + i*3].entityInRoom.name;
        }
        std::cout << ", ";
    }
    std::cout << dungeon [floor - 1].floorMap [26].roomType << std::endl;

    std::cout << "Path 2: ";
    for (unsigned int i = 0; i < 4; i++) { std::cout << dungeon [floor - 1].floorMap [2 + i*3].roomType;
        if (dungeon [floor - 1].floorMap [2 + i*3].roomType == "enemy") {
            std::cout << " - " << dungeon [floor - 1].floorMap [2 + i*3].entityInRoom.name;
        }
        std::cout << ", ";
    }
    std::cout << dungeon [floor - 1].floorMap [13].roomType << ", ";
    for (unsigned int i = 0; i < 4; i++) { std::cout << dungeon [floor - 1].floorMap [15 + i*3].roomType;
        if (dungeon [floor - 1].floorMap [15 + i*3].roomType == "enemy") {
            std::cout << " - " << dungeon [floor - 1].floorMap [15 + i*3].entityInRoom.name;
        }
        std::cout << ", ";
    }
    std::cout << dungeon [floor - 1].floorMap [26].roomType << std::endl;

    std::cout << "Path 3: ";
    for (unsigned int i = 0; i < 4; i++) { std::cout << dungeon [floor - 1].floorMap [3 + i*3].roomType;
        if (dungeon [floor - 1].floorMap [3 + i*3].roomType == "enemy") {
            std::cout << " - " << dungeon [floor - 1].floorMap [3 + i*3].entityInRoom.name;
        }
        std::cout << ", ";
    }
    std::cout << dungeon [floor - 1].floorMap [13].roomType << ", ";
    for (unsigned int i = 0; i < 4; i++) { std::cout << dungeon [floor - 1].floorMap [16 + i*3].roomType;
        if (dungeon [floor - 1].floorMap [16 + i*3].roomType == "enemy") {
            std::cout << " - " << dungeon [floor - 1].floorMap [16 + i*3].entityInRoom.name;
        }
        std::cout << ", ";
    }
    std::cout << dungeon [floor - 1].floorMap [26].roomType << std::endl;
}

void Game::rewardPower (Entity &player) {
    int option_one, option_two, option_three;

    int index = utilityFunctions::random (0, gamePowers.size () - 1);
    option_one = index;

    index = utilityFunctions::random (0, gamePowers.size () - 1);
    option_two = index;

    index = utilityFunctions::random (0, gamePowers.size () - 1);
    option_three = index;

    std::cout << "Choose a power: \n[1] " << gamePowers [option_one].name << "\n[2] " << gamePowers [option_two].name
        << "\n[3] " << gamePowers [option_three].name << std::endl;
    int choice = 1;
    choice = utilityFunctions::getIntegerInput ();

    switch (choice) {
        case 1: {
            player.powers.push_back (&gamePowers [option_one]);
        } break;
        case 2: {
            player.powers.push_back (&gamePowers [option_two]);
        } break;
        case 3: {
            player.powers.push_back (&gamePowers [option_three]);
        } break;
    }
}

void Game::loop (Entity &player) {
    int roomIndex = 0;

    while (player.health > 0) {
        std::cout << player.name << " HP " << player.health << " / " << player.maxHealth << " - " << player.gold << " G" << std::endl;
        displayRoomChoices (roomIndex);

        int choice = -1; choice = utilityFunctions::getIntegerInput ();

        if (roomIndex == 0) { roomIndex = choice;
        } else if (roomIndex >= 10 && roomIndex <= 12) { roomIndex = 13;
        } else if (roomIndex >= 23 && roomIndex <= 25) { roomIndex = 26;
        } else if (roomIndex == 13) { roomIndex = choice + 13;
        } else {
            roomIndex += 3;
        }

        executeRoomLogic (player, roomIndex);

        if (roomIndex == 26) { roomIndex = 0; floor++; std::cout << "You made it to floor " << floor << "!" << std::endl; std::cin.get (); rewardPower (player); }
    }

    if (player.health <= 0) {
        std::cout << "You died..." << std::endl;
        std::cin.get ();

    }

}

void Game::executeRoomLogic (Entity &player, int roomIndex) {
    if (dungeon [floor - 1].floorMap [roomIndex].roomType == "enemy") {
        battle (player, dungeon [floor - 1].floorMap [roomIndex].entityInRoom);

    } else if (dungeon [floor - 1].floorMap [roomIndex].roomType == "shop") {
        shop (player, roomIndex);

    } else if (dungeon [floor - 1].floorMap [roomIndex].roomType == "skillreward") {
        std::cout << "You find an ancient text that teaches you a skill." << std::endl;
        replaceSkill (player, &dungeon [floor - 1].floorMap [roomIndex].skillReward);
    } else {
        std::cout << "You found a chest of gold!" << std::endl;
        player.gold += dungeon [floor - 1].floorMap [roomIndex].goldReward;
    }
}

void Game::shop (Entity &player, int roomIndex) {

    bool looping = true;
    while (looping) {

        std::cout << "SHOP\n[1] Buy Skill " << dungeon [floor - 1].floorMap [roomIndex].skillReward.name << " - "
            << dungeon [floor - 1].floorMap [roomIndex].priceOfSkill << std::endl;
        std::cout << "[2] Heal " << (player.maxHealth / 2) << " HP - " << dungeon [floor - 1].floorMap [roomIndex].priceOfHeal << std::endl;
        std::cout << "[3] Exit" << std::endl;
        int choice = 0; choice = utilityFunctions::getIntegerInput ();

        if (choice == 1) {
            if (player.gold >= dungeon [floor - 1].floorMap [roomIndex].priceOfSkill) {
                player.gold -= dungeon [floor - 1].floorMap [roomIndex].priceOfSkill;
                replaceSkill (player, &dungeon [floor - 1].floorMap [roomIndex].skillReward);

            } else {
                std::cout << "Not enough money!" << std::endl;
            }

        }
        if (choice == 2) {
            if (player.gold >= dungeon [floor - 1].floorMap [roomIndex].priceOfHeal) {
                player.gold -= dungeon [floor - 1].floorMap [roomIndex].priceOfHeal;
                player.health += (player.maxHealth / 2); if (player.health > player.maxHealth) { player.health = player.maxHealth; }

            } else {
                std::cout << "Not enough money!" << std::endl;
            }

        }
        if (choice == 3) { looping = false; }
    }
}
