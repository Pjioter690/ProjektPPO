#include "Alive.hpp"
#include <cmath>
//----Alive----

Alive::Alive(float x, float y, float hp, float dmg, float armor, float speed, float HpRegen)
    : hp(hp), dmg(dmg), armor(armor), speed(speed), position(x, y), HealthRegen(HpRegen){
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
    hp -= enemyDmg * (1.0f - armor / 100.0f);
    if(hp<0)
        hp=0;
    fightClock.restart();
}

void Alive::addArmor(float addArmor)//
{
    armor+=addArmor;
}
void Alive::update(sf::Time deltaTime){}//metoda wirtualna do update

void Alive::animate(sf::Time deltaTime){}//metoda wirtualna do animowania

void Alive::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}
float Alive::getDmg() {return dmg;}
sf::FloatRect Alive::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}
//----Hero----


Hero::Hero(float x, float y, float hp, float dmg, float armor, float energy, float speed,float HpRegen)
    : Alive(x, y, hp, dmg, armor,speed,HpRegen),energy(energy),exp(0),lvl(1), maxenergy(energy), maxExp(10/*przykladowa wartosc do ustalenia*/), maxHp(hp),
    rotation(3/*kierunek zwrócenia siê postaci: 1 oznacza górê, 2 prawo, 3 dó³ a 4 lewo, wykorzystywane w ustawianiu hitboxa broni i potancjalnie w animacji*/) {}


//Metody do uzyskania danych
int Hero::getLevel() {return lvl;}
float Hero::getenergy() {return energy;}
float Hero::getExp() {return exp;}
float Hero::getHp() {return hp;}
float Hero::getmaxenergy() {return maxenergy;}
float Hero::getmaxExp() {return maxExp;}
float Hero::getmaxHp() {return maxHp;}

void Hero::lvlUp()
{
    if (exp >= maxExp)
    {
        exp = exp - maxExp;
        maxExp=maxExp+10;
        lvl++;
        dmg +=1.f;
        if(armor<50)
        {
            armor=armor+1.f;
        }
    }
}

void Hero::animate(const sf::Time& deltaTime) {
    static const int frameSize = 32;
    static const int movementFrames = 4;
    static const int attackFrames = 3;
    static const int deathFrames = 4;
    static float animationSpeed = 0.25f;
    static float deathAnimationSpeed = 0.5f;
    sprite.setOrigin({frameSize / 2, frameSize / 2});
    static int currentFrame = 0;
    static float timer = 0.f;
    static bool isMoving = false;
    static bool isAttacking = false;
    static int attackFrame = 0;

    timer += deltaTime.asSeconds();

    // Śmierć
    if (hp <= 0) {
        if (timer >= deathAnimationSpeed) {
            timer = 0.f;
            currentFrame = (currentFrame + 1) % deathFrames;
        }
        sprite.setTextureRect(sf::IntRect(currentFrame * frameSize, frameSize * 4, frameSize, frameSize));
        sprite.setPosition(position);
        return;
    }

    isMoving = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W) ||
               sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S) ||
               sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) ||
               sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isAttacking) {
        isAttacking = true;
        attackFrame = 0;
        timer = 0.f;
    }

    // Animacja ataku
    if (isAttacking) {
        if (timer >= animationSpeed) {
            timer = 0.f;
            attackFrame++;
            if (attackFrame >= attackFrames) {
                attackFrame = 0;
                isAttacking = false;
            }
        }

        int row = 0;
        switch (rotation) {
            case 0: row = 0; break; // góra
            case 1: row = 3; break; // prawo
            case 2: row = 1; break; // dół
            case 3: row = 2; break; // lewo
        }
        sprite.setTextureRect(sf::IntRect(attackFrame * frameSize, frameSize * 5 + row * frameSize, frameSize, frameSize));
        sprite.setPosition(position);
        return;
    }

    // Animacja ruchu tylko jeśli gracz się porusza
    if (isMoving) {
        if (timer >= animationSpeed) {
            timer = 0.f;
            currentFrame = (currentFrame + 1) % movementFrames;
        }

        int row = 0;
        switch (rotation) {
            case 0: row = 0; break; // góra
            case 1: row = 3; break; // prawo
            case 2: row = 1; break; // dół
            case 3: row = 2; break; // lewo
        }
        sprite.setTextureRect(sf::IntRect(currentFrame * frameSize, row * frameSize, frameSize, frameSize));
    } else {
        // Jeśli nie porusza się i nie atakuje, ustaw domyślną klatkę
        int row = 1;
        switch (rotation) {
            case 0: row = 0; break;
            case 1: row = 3; break;
            case 2: row = 1; break;
            case 3: row = 2; break;
        }
        sprite.setTextureRect(sf::IntRect(frameSize, row * frameSize, frameSize, frameSize));
    }

    sprite.setPosition(position);
}

void Hero::gainExp(float expValue)
{
    exp=exp+expValue;
}
void Hero::regenerate()
{
    //regeneracja Many
    if(energy<maxenergy){
        float timeSinceLastRegen = energyRegenClock.getElapsedTime().asSeconds();
        if(timeSinceLastRegen>=0.05){
            energy = std::min(energy + 5.f, maxenergy);
            energyRegenClock.restart();
        }
    }
    //regeneracja Zdrowia
    float timeOutsideBattle = fightClock.getElapsedTime().asSeconds();
    if(timeOutsideBattle>=10.f){
         if (hp < maxHp) {
            float timeSinceHealthRegen = HpRegenClock.getElapsedTime().asSeconds();
            if (timeSinceHealthRegen >= 1.f) {
                hp = std::min(hp + HealthRegen, maxHp);
                HpRegenClock.restart();
            }
        }
    }
}
void Hero::resetenergy()
{
    energy=0;
}

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
    if(!map1.isWall(nextPosition,10.f)){//gracz porusza się tylko kiedy jego następna pozycja nie będzie znajdywać się w ścianie
            position = nextPosition;
            sprite.setPosition(position);
            weapon->followPlayer(position, rotation);
    }
}
Knight::Knight()
    : Hero(350.0f, 350.0f, 200.0f, 4.f, 20.0f,100.f, 40.f, 2.5f) {
    shape.setFillColor(sf::Color::Red);
    if (!texture.loadFromFile("ProjektPPO\\textures\\rycerz.png"))
        cerr << "Nie udalo sie wczytac tekstury rycerz!\n";
    sprite.setTexture(texture);
}

Wizard::Wizard()
    : Hero(350.0f, 350.0f, 100.0f, 3.f, 0.0f,200.f, 70.f, 1.25f){
    shape.setFillColor(sf::Color::Blue);
    if (!texture.loadFromFile("ProjektPPO\\textures\\czarodziej.png"))
        cerr << "Nie udalo sie wczytac tekstury czarodziej!\n";
    sprite.setTexture(texture);
}

Rogue::Rogue()
    : Hero(350.0f, 350.0f, 150.0f, 4.f, 15.0f,50.f, 100.f, 1.5f) {
    shape.setFillColor(sf::Color::Green);
    if (!texture.loadFromFile("ProjektPPO\\textures\\zlodziej.png"))
        cerr << "Nie udalo sie wczytac tekstury zlodziej!\n";
    sprite.setTexture(texture);
}


//----Enemy----

Enemy::Enemy(float x, float y, float hp, float dmg, float armor, float speed, float height, float width, float expValue): Alive(x, y, hp, dmg, armor,speed, 0.f), frameHeight(height), expValue(expValue),
frameWidth(width),animationTimer(0.0f), directionEnum(Down), isAlive(true), isDying(false), deathAnimationFrame(0),
      attackCooldown(2.0f), attackCooldownTimer(0.0f), isStunned(false), stunDuration(2.0f), stunTimer(0.0f)
{
    sprite.setOrigin(frameWidth / 2.f, frameHeight / 2.f);
    sprite.setPosition(x, y);
}

int Enemy::killedEnemies = 0;

Enemy::~Enemy() = default;

void Enemy::dealDmg(float enemyDmg)
{
    hp -= enemyDmg * (1.0f - armor / 100.0f);
    if (hp <= 0 && !isDying){
        onDeath();
    }

    if (!isStunned){
        isStunned = true;
        stunTimer = 0.0f;
    }
}

void Enemy::onDeath()
{
    isDying = true;
    deathAnimationFrame = 0;
    animationTimer = 0.0f;
    killedEnemies++;
}

void Enemy::attack(Hero& hero) {
    if (!isAlive || isDying || isAttacking) return;

    sf::Vector2f difference = hero.getPosition() - position;
    float distance = sqrt(difference.x * difference.x + difference.y * difference.y);

    if (distance <= frameWidth * 1.5f) {
        isAttacking = true;
        animationTimer = 0.0f;
        attackAnimationFrame = 0;
        hero.dealDmg(dmg);
    }
}

void Enemy::update(const sf::Time& deltaTime,
                   Hero& hero,
                   const std::vector<std::unique_ptr<Enemy>>& enemies,
                   Mapa& map1)
{
    if (!isAlive || isDying) return;
    if (isStunned) { updateStunCooldown(deltaTime); return; }

    sf::Vector2f dir = hero.getPosition() - position;
    float len = std::hypot(dir.x, dir.y);
    if (len != 0) dir /= len;

    if (len < 300.f)
    {
        sf::Vector2f proposed = position + dir * speed * deltaTime.asSeconds();

        // kolizja ze ścianą
        float radius = std::max(frameWidth, frameHeight) / 2.f;
        if (map1.isWall(proposed, radius))
            proposed = position;

        // kolizja z graczem i innymi mobami
        if (!checkCollision(proposed, hero, enemies))
            newPosition = proposed;

        position = newPosition;
        sprite.setPosition(position);
         if (abs(dir.x) > abs(dir.y))
        {
            directionEnum = (dir.x > 0) ? Right : Left;
        }
        else
        {
            directionEnum = (dir.y > 0) ? Down : Up;
        }
        if (attackCooldownTimer > 0.0f)
        {
            attackCooldownTimer -= deltaTime.asSeconds();
        }
        if (attackCooldownTimer <= 0.0f)
        {
        attack(hero);
        attackCooldownTimer = attackCooldown;
        }
    }
}

void Enemy::updateStunCooldown(const sf::Time& deltaTime) {//kiedy przeciwnik jest zaatakowany zostanie ogluszony
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


Zombie::Zombie(float x, float y) : Enemy(x, y, 80.0f, 20.0f, 3.0f, 35.0f, 21.0f, 21.0f, 10)
{
    if (!texture.loadFromFile("ProjektPPO\\textures\\zombie.png"))
        cerr << "Nie udalo sie wczytac tekstury zombie!\n";
}

Goblin::Goblin(float x, float y) : Enemy(x, y, 30.0f, 10.0f, 1.0f, 55.0f, 18.0f, 18.0f, 10)
{
    if (!texture.loadFromFile("ProjektPPO\\textures\\goblin.png"))
        cerr << "Nie udalo sie wczytac tekstury goblina!\n";
}

Ogre::Ogre(float x, float y) : Enemy(x, y, 1000.0f, 50.0f, 20.0f, 3.0f, 64.0f, 64.0f, 1000)
{
    if (!texture.loadFromFile("ProjektPPO\\textures\\ogr.png"))
        cerr << "Nie udalo sie wczytac tekstury ogra!\n";
}
