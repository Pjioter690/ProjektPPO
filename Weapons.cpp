#include"Weapons.hpp"

Weapon::Weapon(){
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
Sword::Sword(){
    weaponHitbox.setSize({20.f,50.f});
    weaponHitbox.setOrigin(10.f,50.f);
}
