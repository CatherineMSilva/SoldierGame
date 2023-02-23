/* --------------------------------------------------------
 * File : soldier.cpp
 * Class: COP 3003, Fall 2022
 * Dev  : Catherine Silva
 * Desc : Lab 1 for a soldier NPC AI demo of structs and
 *        enums
 * -------------------------------------------------------- */

#include <iostream>     //console I/O
#include <cstdlib>      //random numbers
#include <ctime>        //random seed
#include "Character.h"  //character class

//Constants & Types
//---------------------------------------------------------
const int START_LEVEL_DIE = 6;
const int HIT_POINT_DIE = 20;
const int ENCOUNTER_DIE = 20;
const int HIT_CHANCE_DIE = 6;
const int DAMAGE_DIE = 10;

enum SoldierMode { //Integer constant and acts as a user defined date type
    HOMING,     //0
    PATROLLING, //1
    ATTACKING,  //2
    DEFENDING,  //3
    RETREATING  //4
};

//struct Character { //Form of user defined date types
//    int level;
//    int hitPoint;
//    int health;
//}; //character type (structure example)


//Function Proto-types (Declarations)
//---------------------------------------------------------
SoldierMode homing(Character &soldier);
SoldierMode patrolling(Character soldier, Character *enemy);
SoldierMode attacking(Character &soldier, Character &enemy);
SoldierMode defending(Character &soldier, Character &enemy);
SoldierMode retreating(Character &soldier, Character &enemy);
bool hitCheck();
void combat(Character &soldier, Character &enemy);

//Function Definitions
//---------------------------------------------------------

int main() {

    //init random numbers
    std::srand(std::time(NULL));

    int level = std::rand() % START_LEVEL_DIE + 1;
    int hitPoint = std::rand() % HIT_POINT_DIE + 1;

    Character soldier(level, hitPoint);
    soldier.setFullHealth();

    SoldierMode soldierMode = HOMING; // Declared and initialize an int variable

    Character enemy;

// main game loop until soldier dies
    do{
        switch (soldierMode) {
            case HOMING:
                soldierMode = homing(soldier);
                std::cout << "The soldier is healing in Homing" << std::endl;
                break; //end homing

            case PATROLLING:
                soldierMode = patrolling(soldier, &enemy);
                std::cout << "The soldier is patrolling, keeping an eye out for enemies" << std::endl;
                break; //end patrolling

            case ATTACKING:
                soldierMode = attacking(soldier, enemy);
                std::cout << "The soldier is attacking" << std::endl;
                break;

            case DEFENDING:
                soldierMode = defending(soldier, enemy);
                std::cout << "The soldier is defending" << std::endl;
                break;

            case RETREATING:
                soldierMode = retreating(soldier, enemy);
                std::cout << "The soldier is retreating" << std:: endl;

        } //end switch soldier mode

    } while (soldier.getHealth() > 0); // see if soldier is alive


    return 0;
} // end main


/**
 * Handle when soldier is at the fort
 * @param soldier - structure for the soldier
 * @return either HOMING or PATROLLING
 */
SoldierMode homing(Character &soldier) {
    SoldierMode retMode = HOMING;

    // does soldier need to heal?
    if (soldier.getHealth() == soldier.getLevel() * soldier.getHitPoint()) {
        std::cout << "Soldier at full health." << std::endl;
        retMode = PATROLLING;
    }
    else {
        std::cout << "Soldier needs to heal" << std::endl;
    }


    // defining how much soldier heals
    if (soldier.getHealth() < soldier.getLevel() * soldier.getHitPoint()) {
        std::cout << "Soldier is healing, please wait" << std::endl;
        int healing = (soldier.getLevel() * soldier.getHitPoint()) / 4;
        soldier.regainHealth(healing);
        retMode = HOMING;
    }
    else {
        retMode = PATROLLING;
    }

    return retMode;
} // end homing


SoldierMode patrolling(Character soldier, Character *enemy){
    SoldierMode retMode = PATROLLING;

    if (!enemy->getHealth()) {

        //no enemy so check for encounter
        int enemyCheck = std::rand() % ENCOUNTER_DIE + 1;

        if (enemyCheck == 1) {

            int level = std::rand() % START_LEVEL_DIE + 1;
            enemy->setLevel(level);
            int hitPoint = std::rand() % HIT_POINT_DIE + 1;
            enemy->setHitPoint(hitPoint);
            enemy->setFullHealth();
            std::cout << "Soldier has encountered a " << enemy->getLevel()
                      << " level enemy with " << enemy->getHitPoint() << " hit points!" << std::endl;
        } // end encounter check
        else {
            std::cout << "All Clear" << std::endl;
        }
    } //end no enemy
    else {
        if (soldier.getLevel() > enemy->getLevel() + 2){
            retMode = ATTACKING;
        }
        else if (soldier.getLevel() > enemy->getLevel() - 2 ){
            retMode = DEFENDING;
        }
        else{
            retMode = RETREATING;
        }
    }

    return retMode;
} // end patrolling


bool hitCheck(){
    bool hitOccurred;
    int hitChance = std::rand() % HIT_CHANCE_DIE + 1;

    if (hitChance == 1){
        hitOccurred = true;
    }
    else {
        hitOccurred = false;
    }

    return hitOccurred;
}

void combat(Character &soldier, Character &enemy){


    //soldier swinging at enemy
    if (hitCheck()){
        int damage = std::rand() % DAMAGE_DIE + 1;
        enemy.takeDamage(damage);
        std::cout << "The enemy took damage " << damage << std::endl;

    }

    //enemy swinging at soldier
    if (hitCheck()) {
        int damage = std::rand() % DAMAGE_DIE + 1;
        soldier.takeDamage(damage);
        std::cout << "The soldier took damage " << damage << std::endl;
    }

}


SoldierMode attacking(Character &soldier, Character &enemy){
    SoldierMode retMode = ATTACKING;
    combat(soldier, enemy);

    // healing in attacking
    int healing = (soldier.getLevel() * soldier.getHitPoint()) / 10;
    soldier.regainHealth(healing);


    if (enemy.getHealth() == 0){
        retMode = PATROLLING;
        soldier.setFullHealth();
    }
    else if (soldier.getHealth() < (soldier.getLevel() * soldier.getHitPoint()) * .60) {
        retMode = DEFENDING;
    }

    return retMode;

} // end attacking


SoldierMode defending(Character &soldier, Character &enemy){
    SoldierMode retMode = DEFENDING;
    combat(soldier, enemy);

    // healing in defending
    int healing = (soldier.getLevel() * soldier.getHitPoint()) / 8;
    soldier.regainHealth(healing);


    if (enemy.getHealth() == 0){
        retMode = PATROLLING;
    }
    else if (soldier.getHealth() < (soldier.getLevel() * soldier.getHitPoint()) * .40) {
        retMode = RETREATING;
    }

    return retMode;

} // end defending


SoldierMode retreating(Character &soldier, Character &enemy){
    SoldierMode retMode = RETREATING;
    combat(soldier, enemy);

    // healing in defending
    int healing = (soldier.getLevel() * soldier.getHitPoint()) / 6;
    soldier.regainHealth(healing);


    if (enemy.getHealth() == 0){
        retMode = HOMING;
    }
    else if (soldier.getHealth() >= (soldier.getLevel() * soldier.getHitPoint()) * .50
             || enemy.getHealth() >= (enemy.getLevel() * enemy.getHitPoint()) * .50) {
        retMode = DEFENDING;
    }

    return retMode;

} // end retreating
