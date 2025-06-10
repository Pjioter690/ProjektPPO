#ifndef WEAPONS_HPP
#define WEAPONS_HPP

#include <SFML/Graphics.hpp>
#include<vector>
#include"Alive.hpp"

class Weapon{
public:
    Weapon();
    //void attack(float dmg,std::vector<Alive> enemies);
    void followPlayer(sf::Vector2f position, int rotation);
    void draw(sf::RenderWindow window);
private:
    sf::RectangleShape weaponHitbox;
};
class Sword : public Weapon{
    Sword();
};
class Wand : public Weapon{
    Wand();
};
class Knife : public Weapon{
    Knife();
};
#endif // WEAPONS_HPP
