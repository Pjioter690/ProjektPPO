#include "Alive.hpp"

Alive::Alive(float hp, float dmg, float armor)
    : hp(hp), dmg(dmg), armor(armor) {}

Hero::Hero(float hp, float dmg, float armor, float mana)
    : Alive(hp, dmg, armor),mana(mana),exp(0),lvl(1),speed(5.f){}

void Hero::control(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
        position.y -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
        position.y += speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
        position.x -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
        position.x += speed;
    }
}
Knight::Knight()
    : Hero(150.0f, 20.0f, 50.0f, 50.f) {}

Wizard::Wizard()
    : Hero(100.0f, 40.0f, 10.0f, 100.f) {}

Rogue::Rogue()
    : Hero(120.0f, 25.0f, 20.0f, 50.f) {}
