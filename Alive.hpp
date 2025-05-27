#ifndef ALIVE_HPP
#define ALIVE_HPP

#include <SFML/Graphics.hpp>


class Alive{
public:
    Alive(float hp, float dmg, float armor, float speed);
    void Attack(); //pozwala atakowac inne obiekty
    void DealDmg(float enemyDmg); //zadaje obrazenia temu obiektowi
    void addArmor(float armor); //zwieksza armor o zadana wartosc
protected:
    float hp;
    float dmg;
    float armor;
    float speed;
};
class Hero : public Alive{
public:
    void control(); //poruszanie si� postaci�
    void lvlUp(); //zwi�kszanie poziomu postaci
    sf::Vector2f getPosition() const;
protected:
    Hero(float hp, float dmg, float armor, float mana);
private:
    float mana;
    float exp;
    float lvl;
    sf::Vector2f position;
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
//----{Enemy}----
class Enemy : public Alive
{
public:
    void trackPlayer();     //nearby player tracking
    sf::Vector2f getPosition() const;
protected:
    Enemy(float hp, float dmg, float armor, float speed);
private:
    sf::Vector2f position;
};

class Zombie : public Enemy
{
    Zombie();
};

class Goblin : public Enemy
{
    Goblin();
};
#endif
