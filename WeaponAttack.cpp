#include"Weapons.hpp"
#include"Alive.hpp"

void Weapon::attack(float dmg,std::vector<std::unique_ptr<Enemy>>& enemies){
    for (auto& enemy : enemies) {
        if (weaponHitbox.getGlobalBounds().intersects(enemy->getGlobalBounds())) {
            enemy->dealDmg(dmg);  // zak³adamy, ¿e Enemy ma metodê `takeDamage(float)`
        }
    }
}
