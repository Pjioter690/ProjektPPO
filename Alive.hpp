#ifndef ALIVE_HPP
#define ALIVE_HPP

#include <SFML/Graphics.hpp>


class Alive{
public:
    Alive(float hp, float dmg, float armor);
    void Attack(); //pozwala atakowac inne obiekty
    void DealDmg(float enemyDmg); //zadaje obrazenia temu obiektowi
    void addArmor(float armor); //zwieksza armor o zadana wartosc
protected:
    float hp;
    float dmg;
    float armor;
};
class Hero : public Alive{
public:
    void control(); //poruszanie siê postaci¹
    void lvlUp(); //zwiêkszanie poziomu postaci
    sf::Vector2f getPosition() const;
protected:
    Hero(float hp, float dmg, float armor, float mana);
private:
    float mana;
    float exp;
    float lvl;
    sf::Vector2f position;
    float speed;
};
class Knight : public Hero{
public:
    Knight();
};
class Wizard : public Hero{
public:
    Wizard();
};
class Rogue : public Hero{
public:
    Rogue();
};
#endif
