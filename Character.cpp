/* --------------------------------------------------------
 * File : Character.cpp
 * Class: COP 3003, Fall 2022
 * Dev  : Catherine Silva
 * Desc : Implementation of a character class object
 * -------------------------------------------------------- */
#include "Character.h"


// Constructors
//-----------------------------------------------------
Character::Character(){
    level = 0;
    hitPoint = 0;
    health = 0;
} // default constructor

Character::Character(int level, int hitPoint){
    this->level = level;
    this->hitPoint = hitPoint;
    //this->health = health;
} // property constructor


// Accessors
//-----------------------------------------------------
int Character::getLevel(){ return level; }
void Character::setLevel(int value){ level = value; }

int Character::getHitPoint(){ return hitPoint; }
void Character::setHitPoint(int value){ hitPoint = value; }

int Character::getHealth(){ return health; } // read only property


// Method
//-----------------------------------------------------
void Character::setFullHealth() {
    health = level * hitPoint;
}

bool Character::isFullHealth() {
    return health == hitPoint * level;
}

void Character::takeDamage(int damage) {
    health -= damage;

    if (health < 0) {
        health = 0;
    }
}

void Character::regainHealth(int healing) {
    health += healing;

    if (health > 120){
        health = 120;
    }
}