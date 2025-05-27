#include "Alive.hpp"

//----Alive----

Alive::Alive(float hp, float dmg, float armor, float speed)
    : hp(hp), dmg(dmg), armor(armor) {}

sf::Vector2f Alive::getPosition() const
{
    return position;
}

void Alive::addArmor(float addArmor)
{
    armor+=addArmor;
}
void Alive::update()
{
    //Work in Progress
}

void Alive::animate()
{
    //Work in Progress
}
//----Hero----

Hero::Hero(float hp, float dmg, float armor, float mana)
    : Alive(hp, dmg, armor,5.f),mana(mana),exp(0),lvl(1){}

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
    : Hero(200.0f, 20.0f, 5.0f, 50.f) {}

Wizard::Wizard()
    : Hero(100.0f, 40.0f, 0.0f, 100.f) {}

Rogue::Rogue()
    : Hero(150.0f, 25.0f, 2.0f, 50.f) {}


//----Enemy----

Enemy::Enemy(float hp, float dmg, float armor, float speed)
     : Alive(hp, dmg, armor,speed){}

void Enemy::trackPlayer()
{
    //Work in Progress
}

Zombie::Zombie()
      : Enemy(100.0f, 20.0f, 30.0f, 2.5f) {}

Goblin::Goblin()
      : Enemy(50.0f, 10.0f, 15.0f, 6.0f) {}

Skeleton::Skeleton()
        : Enemy(10.0f, 25.0f, 20.0f, 4.5f) {}

Boss::Boss()
    : Enemy(1000.0f, 50.0f, 35.0f, 3.0f) {}
