#ifndef ALIVE_HPP
#define ALIVE_HPP

#include <SFML/Graphics.hpp>


class Alive{
public:
    Alive(float hp, float dmg, float armor, float speed);
    void Attack(); //pozwala atakowac inne obiekty
    void dealDmg(float enemyDmg); //zadaje obrazenia temu obiektowi
    void addArmor(float armor); //zwieksza armor o zadana wartosc
    void update();
    void animate();
    sf::Vector2f getPosition() const;
    virtual void draw(sf::RenderWindow& window);
protected:
    sf::Texture texture;
    sf::Vector2f position;
    sf::CircleShape shape;
    float hp;
    float dmg;
    float armor;
    float speed;
};
class Hero : public Alive{
public:
    void control(sf::Time deltaTime); //poruszanie siê postaci¹
    void lvlUp(); //zwiêkszanie poziomu postaci

    //Metody do uzyskania danych
    float getMana();
    float getExp();
    float getHp();
    float getmaxMana();
    float getmaxExp();
    float getmaxHp();

protected:
    Hero(float hp, float dmg, float armor, float mana);
private:
    float mana;
    float exp;
    float lvl;
    float maxMana;
    float maxExp;
    float maxHp;
    //sf::Vector2f position;
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
    void trackPlayer(const sf::Vector2f& playerPos);            //sledzenie najblizszego gracza
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

class Skeleton : public Enemy
{
    Skeleton();
};

class Boss : public Enemy
{
    Boss();
};
#endif
