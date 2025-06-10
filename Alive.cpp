#include "Alive.hpp"
#include <cmath>
//----Alive----

Alive::Alive(float x, float y, float hp, float dmg, float armor, float speed)
    : hp(hp), dmg(dmg), armor(armor), speed(speed), position(x, y){
    shape.setRadius(20.f);
    shape.setOrigin({20.f, 20.f});
    shape.setFillColor(sf::Color::White);
    sprite.setTexture(texture);
}

sf::Vector2f Alive::getPosition() const
{
    return position;
}
void Alive::dealDmg(float enemyDmg)
{
    hp -=(enemyDmg*(100-armor));
    cout<<hp<<endl;
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
float Alive::getDmg() {return dmg;}
sf::FloatRect Alive::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}
//----Hero----

Hero::Hero(float x, float y, float hp, float dmg, float armor, float mana)
    : Alive(x, y, hp, dmg, armor,150.f),mana(mana),exp(0),lvl(1), maxMana(mana), maxExp(100/*przykladowa wartosc do ustalenia*/), maxHp(hp),
    rotation(3/*kierunek zwrócenia siê postaci: 1 oznacza górê, 2 prawo, 3 dó³ a 4 lewo, wykorzystywane w ustawianiu hitboxa broni i potancjalnie w animacji*/) {}


//Metody do uzyskania danych
float Hero::getMana() {return mana;}
float Hero::getExp() {return exp;}
float Hero::getHp() {return hp;}
float Hero::getmaxMana() {return maxMana;}
float Hero::getmaxExp() {return maxExp;}
float Hero::getmaxHp() {return maxHp;}


void Hero::control(sf::Time deltaTime, Mapa map1,Weapon* weapon){
    sf::Vector2f nextPosition = position;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
        nextPosition.y -= speed*deltaTime.asSeconds();
        rotation = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
        nextPosition.y += speed*deltaTime.asSeconds();
        rotation = 2;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
        nextPosition.x -= speed*deltaTime.asSeconds();
        rotation = 3;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
        nextPosition.x += speed*deltaTime.asSeconds();
        rotation = 1;
    }
    if(!map1.isWall(nextPosition,20.f)){
            position = nextPosition;
            shape.setPosition(position);
            weapon->followPlayer(position, rotation);
    }
}
Knight::Knight()
    : Hero(350.0f, 350.0f, 200.0f, 20.0f, 5.0f, 50.f) {
    shape.setFillColor(sf::Color::Red);
}

Wizard::Wizard()
    : Hero(350.0f, 350.0f, 100.0f, 40.0f, 0.0f, 100.f) {
    shape.setFillColor(sf::Color::Blue);
}

Rogue::Rogue()
    : Hero(350.0f, 350.0f, 150.0f, 25.0f, 2.0f, 50.f) {
    shape.setFillColor(sf::Color::Green);
}


//----Enemy----

Enemy::Enemy(float x, float y, float hp, float dmg, float armor, float speed): Alive(x, y, hp, dmg, armor,speed), frameHeight(32.f),
frameWidth(32.f) {}

int Enemy::killedEnemies = 0;

Enemy::~Enemy() = default;

void Enemy::dealDmg(float enemyDmg)
{
    hp -=(enemyDmg*(100-armor));
    //cout << "Przeciwnik otrzymal obrazenia, zostalo mu " << hp << " punktow zycia.\n";
    if (hp <= 0 && !isDying) {
        onDeath();
    }
    if (!isStunned) {
        isStunned = true;
        stunTimer = 0.0f;
    }
}

void Enemy::onDeath() {
    isDying = true;
    deathAnimationFrame = 0;
    animationTimer = 0.0f;
    killedEnemies++;
    cout << "Liczba zabitych przeciwników: " << killedEnemies << endl;
}

void Enemy::update(const sf::Time& deltaTime, Hero& hero, const vector<std::unique_ptr<Enemy>>& enemies)
{
    if (!isAlive || isDying)//brak update'u jesli obiekt jest martwy lub umierajacy
        return;
    if (isStunned)
    {
        updateStunCooldown(deltaTime);
        return;
    }
    sf::Vector2f direction = hero.getPosition() - position;
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
    {
        direction /= length;
    }
    if(length<300.0f)
    {
        sf::Vector2f nextPosition = position + direction * speed * deltaTime.asSeconds();
        if (!checkCollision(nextPosition, hero, enemies))
        {
            newPosition = nextPosition;
        }

        position = newPosition;
        sprite.setPosition(position);

        if (abs(direction.x) > abs(direction.y))
        {
            directionEnum = (direction.x > 0) ? Right : Left;
        }
        else
        {
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
}

void Enemy::updateStunCooldown(const sf::Time& deltaTime) {
    if (isStunned) {
        stunTimer += deltaTime.asSeconds();
        if (stunTimer >= stunDuration) {
            isStunned = false;
        }
    }
}

bool Enemy::checkCollision(const sf::Vector2f& newPos, Hero& hero, const vector<unique_ptr<Enemy>>& enemies) const {
    sf::FloatRect enemyBounds(newPos.x - frameWidth / 2.f, newPos.y - frameHeight / 2.f, frameWidth, frameHeight);
    sf::FloatRect heroBounds(hero.getPosition().x - 7.f, hero.getPosition().y - 12.f, 14.f, 24.f); // również środek

    if (enemyBounds.intersects(heroBounds))
    {
        return true;
    }

    for (const auto& other : enemies)
    {
        if (other.get() == this || !other->GetisAlive())
            continue;

        sf::FloatRect otherBounds(other->getPosition().x - other->frameWidth / 2.f,
                                  other->getPosition().y - other->frameHeight / 2.f,
                                  other->frameWidth, other->frameHeight);

        if (enemyBounds.intersects(otherBounds))
            return true;
    }

    return false;
}


bool Enemy::GetisAlive() const
{
    return isAlive;
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
        if (animationTimer >= 0.3f)
        {
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
    if (!isAlive && !isDying) return; //nie rysuje gdy nie zyje
    window.draw(sprite);
}


Zombie::Zombie(float x, float y) : Enemy(x, y, 100.0f, 20.0f, 3.0f, 35.0f)
{
    if (!texture.loadFromFile("ProjektPPO\\textures\\zombie.png")) {
        cerr << "Nie udalo sie wczytac tekstury zombie!\n";
    }

    sprite.setOrigin(frameWidth / 2.f, frameHeight / 2.f); // Wyśrodkowanie sprite'a
    sprite.setPosition(x, y);

    cout << "Utworzono Zombie\n";
}

Goblin::Goblin(float x, float y) : Enemy(x, y, 50.0f, 10.0f, 1.0f, 55.0f)
{
    if (!texture.loadFromFile("ProjektPPO\\textures\\goblin.png")) {
        cerr << "Nie udalo sie wczytac tekstury goblina!\n";
    }

    sprite.setOrigin(frameWidth / 2.f, frameHeight / 2.f);
    sprite.setPosition(x, y);
}

Ogre::Ogre(float x, float y) : Enemy(x, y, 1000.0f, 50.0f, 20.0f, 3.0f)
{
    if (!texture.loadFromFile("ProjektPPO\\textures\\ogr.png")) {
        cerr << "Nie udalo sie wczytac tekstury ogra!\n";
    }

    sprite.setOrigin(frameWidth / 2.f, frameHeight / 2.f);
    sprite.setPosition(x, y);
}
