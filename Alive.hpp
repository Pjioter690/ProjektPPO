#ifndef ALIVE_HPP
#define ALIVE_HPP

#include <SFML/Graphics.hpp>
#include"Map.hpp"
#include"Weapons.hpp"
#include<vector>
#include<memory>


class Alive{
public:
    Alive(float x, float y, float hp, float dmg, float armor, float speed);
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
    void control(sf::Time deltaTime,Mapa map1,Weapon*); //poruszanie siê postaci¹
    void lvlUp(); //zwiêkszanie poziomu postaci

    //Metody do uzyskania danych
    float getMana();
    float getExp();
    float getHp();
    float getmaxMana();
    float getmaxExp();
    float getmaxHp();

protected:
    Hero(float x, float y, float hp, float dmg, float armor, float mana);
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
    void update(const sf::Time& deltaTime, Hero& hero, const vector<std::unique_ptr<Enemy>>& enemies);
    virtual void draw(sf::RenderWindow& window);
    virtual void animate(const sf::Time& deltaTime);
    bool GetisAlive() const;
protected:
    Enemy(float x, float y, float hp, float dmg, float armor, float speed);

    int frameWidth, frameHeight;
    bool isAlive = true;
    bool isDying = false;
    bool isAttacking = false;


    enum Direction { Up, Down, Left, Right } directionEnum = Down;
    int attackAnimationFrame, deathAnimationFrame, animationFrame;
    float animationTimer;
    bool checkCollision(const sf::Vector2f& newPos, Hero& hero, const vector<unique_ptr<Enemy>>& enemies) const;

    void updateStunCooldown(const sf::Time& deltaTime);
    float stunDuration = 1.0f;
    float stunTimer = 0.0f;
    bool isStunned = false;

    sf::Vector2f newPosition;
};

class Zombie : public Enemy
{
    public:
    Zombie(float x, float y);
};

class Goblin : public Enemy
{
    public:
    Goblin(float x, float y);
};


class Ogre : public Enemy
{
    public:
    Ogre(float x, float y);
};
#endif
