#include "Alive.hpp"
#include <cmath>
//----Alive----

Alive::Alive(float hp, float dmg, float armor, float speed)
    : hp(hp), dmg(dmg), armor(armor), speed(speed), position(250.f, 250.f){
    shape.setRadius(20.f);
    shape.setOrigin({20.f, 20.f});
    shape.setFillColor(sf::Color::White);
}

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
    animate();
    shape.setPosition(position);
}

void Alive::animate()
{
    //Work in Progress
}
void Alive::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}
//----Hero----

Hero::Hero(float hp, float dmg, float armor, float mana)
    : Alive(hp, dmg, armor,150.f),mana(mana),exp(0),lvl(1), maxMana(mana), maxExp(100/*przykladowa wartosc do ustalenia*/), maxHp(hp) {}


//Metody do uzyskania danych
float Hero::getMana() {return mana;}
float Hero::getExp() {return exp;}
float Hero::getHp() {return hp;}
float Hero::getmaxMana() {return maxMana;}
float Hero::getmaxExp() {return maxExp;}
float Hero::getmaxHp() {return maxHp;}


void Hero::control(sf::Time deltaTime, Mapa map1){
    std::vector<Mapa> kopiaMapy = map1.getTiles();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
        position.y -= speed*deltaTime.asSeconds();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
        position.y += speed*deltaTime.asSeconds();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
        position.x -= speed*deltaTime.asSeconds();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
        position.x += speed*deltaTime.asSeconds();
    }
}
Knight::Knight()
    : Hero(200.0f, 20.0f, 5.0f, 50.f) {
    shape.setFillColor(sf::Color::Red);
}

Wizard::Wizard()
    : Hero(100.0f, 40.0f, 0.0f, 100.f) {
    shape.setFillColor(sf::Color::Blue);
}

Rogue::Rogue()
    : Hero(150.0f, 25.0f, 2.0f, 50.f) {
    shape.setFillColor(sf::Color::Green);
}


//----Enemy----

Enemy::Enemy(float hp, float dmg, float armor, float speed)
     : Alive(hp, dmg, armor,speed){}

void Enemy::trackPlayer(const sf::Vector2f& playerPos)
{
    sf::Vector2f dir = playerPos - position;
    float distance = sqrt(dir.x * dir.x + dir.y * dir.y);
    const float detectionradius = 200.0f;
    if (distance < detectionradius)
    {
        dir.x /= distance;
        dir.y /= distance;
        position.x+=dir.x*speed;
        position.y+=dir.y*speed;
    }
}

Zombie::Zombie()
      : Enemy(100.0f, 20.0f, 3.0f, 2.5f) {}

Goblin::Goblin()
      : Enemy(50.0f, 10.0f, 1.0f, 6.0f) {}

Skeleton::Skeleton()
        : Enemy(10.0f, 25.0f, 2.0f, 4.5f) {}

Boss::Boss()
    : Enemy(1000.0f, 50.0f, 20.0f, 3.0f) {}
