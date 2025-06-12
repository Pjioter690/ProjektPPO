#ifndef ALIVE_HPP
#define ALIVE_HPP

#include <SFML/Graphics.hpp>
#include"Map.hpp"
#include"Weapons.hpp"
#include<vector>
#include<memory>


class Alive{
public:
    Alive(float x, float y, float hp, float dmg, float armor, float speed,float HpRegen);
    void Attack(); //pozwala atakowac inne obiekty
    virtual void dealDmg(float enemyDmg); //zadaje obrazenia temu obiektowi
    void addArmor(float armor); //zwieksza armor o zadana wartosc
    virtual void update(sf::Time deltaTime);
    virtual void animate(sf::Time deltaTime);
    sf::Vector2f getPosition() const;
    virtual void draw(sf::RenderWindow& window);
    float getDmg();
    sf::FloatRect getGlobalBounds() const;
    sf::Clock fightClock; //liczy czas spędzony poza walką
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;
    sf::CircleShape shape;
    float hp;
    float dmg;
    float armor;
    float speed;
    float HealthRegen;
    enum Direction { Up, Down, Left, Right } directionEnum = Down;
};
class Hero : public Alive{
public:
    void control(sf::Time deltaTime,Mapa map1,Weapon*); //poruszanie siê postaci¹
    void lvlUp(); //zwiêkszanie poziomu postaci
    void gainExp();
    sf::Clock energyRegenClock;
    sf::Clock HpRegenClock;
    void resetenergy();
    void regenerate();
    void animate(const sf::Time& deltaTime);

    //Metody do uzyskania danych
    float getenergy();
    float getExp();
    float getHp();
    float getmaxenergy();
    float getmaxExp();
    float getmaxHp();
    int getLevel();

protected:
    Hero(float x, float y, float hp, float dmg, float armor, float energy, float speed,float HpRegen);
    float animationTimer;
    float frameWidth, frameHeight;
    sf::Texture texture;
private:
    float energy;
    float exp;
    float lvl;
    float maxenergy;
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
    virtual ~Enemy();
    void dealDmg(float enemyDmg);
    void update(const sf::Time& deltaTime, Hero& hero, const vector<std::unique_ptr<Enemy>>& enemies, Mapa& map1);
    void draw(sf::RenderWindow& window);
    void animate(const sf::Time& deltaTime);
    bool GetisAlive() const;
protected:
    Enemy(float x, float y, float hp, float dmg, float armor, float speed, float height, float width);

    void attack(Hero& hero);
    float attackCooldown, attackCooldownTimer;

    int frameWidth, frameHeight;
    bool isAlive;
    bool isDying;
    bool isAttacking;
    float stunDuration;
    float stunTimer;
    bool isStunned;
    void onDeath();
    enum Direction { Up, Down, Left, Right } directionEnum = Down;
    int attackAnimationFrame, deathAnimationFrame, animationFrame;
    float animationTimer;
    bool checkCollision(const sf::Vector2f& newPos, Hero& hero, const vector<unique_ptr<Enemy>>& enemies) const;

    void updateStunCooldown(const sf::Time& deltaTime);

    static int killedEnemies;
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
