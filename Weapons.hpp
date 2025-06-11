#ifndef WEAPONS_HPP
#define WEAPONS_HPP

#include <SFML/Graphics.hpp>
#include<vector>
#include<memory>

class Alive;
class Enemy;
class Hero;

class Weapon{
public:
    Weapon(float dmg, float cooldown);
    void attack(float dmg,std::vector<std::unique_ptr<Enemy>>& enemies,float energy, float maxenergy,Hero*hero);
    void followPlayer(sf::Vector2f position, int rotation);
    float getDmg();
    void draw(sf::RenderWindow& window);
    sf::Clock attackClock;
protected:
    sf::RectangleShape weaponHitbox;
    float dmg;
    float cooldown;
};
class Sword : public Weapon{
public:
    Sword();
};
class Wand : public Weapon{
public:
    Wand();
};
class Knife : public Weapon{
public:
    Knife();
};

#endif // WEAPONS_HPP
