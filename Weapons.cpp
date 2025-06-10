#include"Weapons.hpp"

Weapon::Weapon(float dmg):dmg(dmg){
    //weaponHitbox.setFillColor(sf::Color::Transparent);
    weaponHitbox.setFillColor(sf::Color::Black);
    weaponHitbox.setRotation(90.f);
    weaponHitbox.setPosition({350.f,350.f});
}
/*void Weapons::attack(float dmg,std::vector<Alive> enemies){
    for(auto enemy : enemies)
        if()

}*/
void Weapon::followPlayer(sf::Vector2f position,int rotation){
    weaponHitbox.setPosition(position);
    weaponHitbox.setRotation(rotation*90.f);
}
void Weapon::draw(sf::RenderWindow& window){
    window.draw(weaponHitbox);
}
Sword::Sword():Weapon(2){
    weaponHitbox.setSize({20.f,50.f});
    weaponHitbox.setOrigin(10.f,50.f);
}
Wand::Wand():Weapon(4){
    weaponHitbox.setSize({20.f,100.f});
    weaponHitbox.setOrigin(10.f,100.f);
}
Knife::Knife():Weapon(3){
    weaponHitbox.setSize({15.f,20.f});
    weaponHitbox.setOrigin(7.5f,20.f);
}
