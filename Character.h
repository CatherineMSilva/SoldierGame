/* --------------------------------------------------------
 * File : Character.h
 * Class: COP 3003, Fall 2022
 * Dev  : Catherine Silva
 * Desc : Declaration of a Character class object
 * -------------------------------------------------------- */

// HEADER GUARD
#ifndef SOLDIER_CHARACTER_H
#define SOLDIER_CHARACTER_H
// you can declare global constant like med health

class Character{
private:
    int level;
    int hitPoint;
    int health;

public:
    // Constructors
    //-----------------------------------------------------
    Character(); // default constructor

    Character(int level, int hitPoint); // property constructor

    // Accessors
    //-----------------------------------------------------
    int getLevel();
    void setLevel(int value);

    int getHitPoint();
    void setHitPoint(int value);

    int getHealth(); // read only property

    // Method
    //-----------------------------------------------------
    void setFullHealth();

    bool isFullHealth();

    void takeDamage(int damage);

    void regainHealth(int healing);
};

#endif //SOLDIER_CHARACTER_H
