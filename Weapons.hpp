#ifndef WEAPONS_HPP
#define WEAPONS_HPP

#include <SFML/Graphics.hpp>
#include<vector>

class Alive;

class Weapon{
public:
    Weapon();
    void attack(float dmg,std::vector<Alive> enemies);
    void followPlayer(sf::Vector2f position, int rotation);
    void draw(sf::RenderWindow& window);
protected:
    sf::RectangleShape weaponHitbox;
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
