#include "Alive.hpp"
#include <cmath>
//----Alive----

Alive::Alive(float hp, float dmg, float armor, float speed)
    : hp(hp), dmg(dmg), armor(armor), speed(speed), position(350.f, 350.f){
    shape.setRadius(20.f);
    shape.setOrigin({20.f, 20.f});
    shape.setFillColor(sf::Color::White);
    sprite.setTexture(texture);
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
    sf::Vector2f nextPosition = position;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
        nextPosition.y -= speed*deltaTime.asSeconds();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
        nextPosition.y += speed*deltaTime.asSeconds();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
        nextPosition.x -= speed*deltaTime.asSeconds();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
        nextPosition.x += speed*deltaTime.asSeconds();
    }
    if(!map1.isWall(nextPosition,20.f)){
            position = nextPosition;
            shape.setPosition(position);
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

Enemy::Enemy(float hp, float dmg, float armor, float speed): Alive(hp, dmg, armor,speed),isAlive(true), isDying(false), animationTimer(0.0f), deathAnimationFrame(0),
animationFrame(1), frameHeight(32), frameWidth(32), position(0,0), directionEnum(Down)

{
    sprite.setTextureRect(sf::IntRect(frameWidth + 1, frameHeight + 1, frameWidth, frameHeight));

}

void Enemy::update(const sf::Time& deltaTime, Hero& hero)
{
    /*if (!isAlive || isDying) return; //brak update'u jesli obiekt jest martwy lub umierajacy

    if (isStunned)
    {
        //updateCooldown(deltaTime);
        return;
    }*/
    sf::Vector2f direction = hero.getPosition() - position;

    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
    {
        direction /= length;
    }
    sf::Vector2f nextPosition = position + direction * speed * deltaTime.asSeconds();
        //if (!checkCollision(tempPos, hero)) {
        //    newPos = tempPos;
        //} //else {
          //  break;
        //}
    //}
    position = nextPosition;
    sprite.setPosition(position);

    if (abs(direction.x) > abs(direction.y)) {
        directionEnum = (direction.x > 0) ? Right : Left;
    } else {
        directionEnum = (direction.y > 0) ? Down : Up;
    }

    //if (attackCooldownTimer > 0.0f) {
      //  attackCooldownTimer -= deltaTime.asSeconds();
    //}

    //if (attackCooldownTimer <= 0.0f) {
      //  attack(player);
        //attackCooldownTimer = attackCooldown;
    //}
}

void Enemy::animate(const sf::Time& deltaTime)
{
    animationTimer += deltaTime.asSeconds();
    if (isDying)
    {
        if (animationTimer >= 0.3f)
        {
            animationTimer = 0.0f;
            deathAnimationFrame++;
            if (deathAnimationFrame >= 4)
            {
                isDying = false;
                isAlive = false;
                return;
            }
        }

        sprite.setTextureRect(sf::IntRect(deathAnimationFrame * frameWidth + 1, frameHeight * 4 + 1, frameWidth, frameHeight));
        return;
    }
    if (isAttacking)
        {
            if (animationTimer >= 0.3f)
            {
                animationTimer = 0.0f;
                attackAnimationFrame++;
                if (attackAnimationFrame >= 3)
                {
                    isAttacking = false;
                    attackAnimationFrame = 0;
                }
            }
            int attackDirectionOffset;
            switch (directionEnum)
            {
                case Up:    attackDirectionOffset = frameHeight * 0; break;
                case Down:  attackDirectionOffset = frameHeight * 1; break;
                case Left:  attackDirectionOffset = frameHeight * 2; break;
                case Right: attackDirectionOffset = frameHeight * 3; break;
            }
            sprite.setTextureRect(sf::IntRect(attackAnimationFrame * frameWidth + 1, frameHeight * 5 + attackDirectionOffset + 1, frameWidth, frameHeight));
            return;
        }
    if (!isStunned)
        {
        if (animationTimer >= 0.3f) {
            animationFrame = (animationFrame + 1) % 3;
            animationTimer = 0.f;
        }
    }

    int MovingDirection;
    switch (directionEnum)
    {
        case Up: MovingDirection = frameHeight * 0; break;
        case Down: MovingDirection = frameHeight * 1; break;
        case Left: MovingDirection = frameHeight * 2; break;
        case Right: MovingDirection = frameHeight * 3; break;
    }

    sprite.setTextureRect(sf::IntRect(animationFrame * frameWidth + 1, MovingDirection + 1, frameWidth, frameHeight));
}

void Enemy::draw(sf::RenderWindow& window)
{
    if (!isAlive && !isDying) return;

    window.draw(sprite);
}


Zombie::Zombie(): Enemy(100.0f, 20.0f, 3.0f, 35.0f)
{
    if (!texture.loadFromFile("ProjektPPO\\textures\\zombie.png"))
        {
        cerr << "Nie udalo sie wczytac tekstury zombie!\n";
        }
        sprite.setPosition(0,0);
}

Goblin::Goblin(): Enemy(50.0f, 10.0f, 1.0f, 55.0f)
{
    if (!texture.loadFromFile("ProjektPPO\\textures\\goblin.png"))
        {
        cerr << "Nie udalo sie wczytac tekstury goblina!\n";
        }
}

Ogre::Ogre(): Enemy(1000.0f, 50.0f, 20.0f, 3.0f)
{
    if (!texture.loadFromFile("ProjektPPO\\textures\\ogr.png"))
        {
        cerr << "Nie udalo sie wczytac tekstury ogra!\n";
        }
}
