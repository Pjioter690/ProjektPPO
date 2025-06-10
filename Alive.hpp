#ifndef ALIVE_HPP
#define ALIVE_HPP

#include <SFML/Graphics.hpp>
#include"Map.hpp"
#include"Weapons.hpp"
#include<vector>


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
    sf::Sprite sprite;
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
    void control(sf::Time deltaTime,Mapa map1); //poruszanie siê postaci¹
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
    Weapon herosWeapon;
private:
    float mana;
    float exp;
    float lvl;
    float maxMana;
    float maxExp;
    float maxHp;
    int rotation;
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
    void update(const sf::Time& deltaTime, Hero& hero);
    virtual void draw(sf::RenderWindow& window);
    virtual void animate(const sf::Time& deltaTime);
protected:
    int frameWidth, frameHeight, deathAnimationFrame, animationFrame;
    int attackAnimationFrame = 0;
    float animationTimer;
    bool isAlive, isDying, isStunned;
    bool isAttacking = false;
    Enemy(float hp, float dmg, float armor, float speed);
    enum Direction { Up, Down, Left, Right } directionEnum;
private:
    sf::Vector2f position;
};

class Zombie : public Enemy
{
    public:
    Zombie(int x, int y);
};

class Goblin : public Enemy
{
    public:
    Goblin();
};


class Ogre : public Enemy
{
    public:
    Ogre();
};
#endif
