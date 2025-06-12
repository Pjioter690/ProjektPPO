#include"Weapons.hpp"

Weapon::Weapon(float dmg, float cooldown):dmg(dmg),cooldown(cooldown){
    weaponHitbox.setFillColor(sf::Color::Transparent);
    weaponHitbox.setRotation(90.f);
    weaponHitbox.setPosition({350.f,350.f});//poczatkowa pozycja gracza
}

void Weapon::followPlayer(sf::Vector2f position,int rotation){
    weaponHitbox.setPosition(position);//hitbox broni podaza za graczem
    weaponHitbox.setRotation(rotation*90.f); //hitbox broni obraca sie zaleznie od obrotu gracza
}
void Weapon::draw(sf::RenderWindow& window){
    window.draw(weaponHitbox);
}
Sword::Sword():Weapon(2,1){
    weaponHitbox.setSize({20.f,50.f}); //kazda z broni ma inny zasieg
    weaponHitbox.setOrigin(10.f,50.f);
}
Wand::Wand():Weapon(4,2){
    weaponHitbox.setSize({20.f,100.f});
    weaponHitbox.setOrigin(10.f,100.f);
}
Knife::Knife():Weapon(3,0.5){
    weaponHitbox.setSize({15.f,20.f});
    weaponHitbox.setOrigin(7.5f,20.f);
}
