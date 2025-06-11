#include"Weapons.hpp"
#include"Alive.hpp"

void Weapon::attack(float d,std::vector<std::unique_ptr<Enemy>>& enemies,float energy, float maxenergy,Hero* hero){
    if(energy==maxenergy){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            for (auto& enemy : enemies) {
                if (weaponHitbox.getGlobalBounds().intersects(enemy->getGlobalBounds())) {
                    enemy->dealDmg(d*this->dmg);
                }
            }
            hero->resetenergy();
        }
    }
}
