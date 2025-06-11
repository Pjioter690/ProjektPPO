#include"Weapons.hpp"
#include"Alive.hpp"

void Weapon::attack(float d,std::vector<std::unique_ptr<Enemy>>& enemies){
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        for (auto& enemy : enemies) {
            if (weaponHitbox.getGlobalBounds().intersects(enemy->getGlobalBounds())) {
                enemy->dealDmg(d);
            }
        }
    }
}
