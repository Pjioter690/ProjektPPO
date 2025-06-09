#include "Map.hpp"

Mapa::Mapa(){
    std::string line;
    int row = 0;
    tile.setSize({100.f,100.f});
    wall.setSize({100.f,100.f});
    std::ifstream file("ProjektPPO\\maps\\map1.txt");
    if (!file) {
        cerr<< "Nie mo¿na otworzyæ pliku\n";
    }

    while (std::getline(file, line)) {
        for (std::size_t col = 0; col < line.size(); ++col) {
            if (line[col] == '1') {
                sf::RectangleShape tile({100.f, 100.f});
                tile.setPosition(col * 100.f, row * 100.f);
                tile.setFillColor(sf::Color::White);
                tiles.push_back(tile);
            }
            else if (line[col] == '0') {
                sf::RectangleShape tile({100.f, 100.f});
                tile.setPosition(col * 100.f, row * 100.f);
                tile.setFillColor(sf::Color::Cyan);
                tiles.push_back(tile);
            }
        }
        ++row;
    }
}
void Mapa::draw(sf::RenderWindow& window){
    for(auto tile : tiles){
        window.draw(tile);
    }
}
bool Mapa::isWall(sf::Vector2f position, float radius){
    sf::CircleShape PlayerCharacter;
    PlayerCharacter.setRadius(radius);
    sf::FloatRect bounds = PlayerCharacter.getLocalBounds();
    PlayerCharacter.setOrigin({bounds.left + bounds.width / 2.f,
                       bounds.top + bounds.height / 2.f});
    PlayerCharacter.setPosition(position);
    sf::FloatRect playerBounds = PlayerCharacter.getGlobalBounds();
    for (const auto& tile : tiles) {

        if (tile.getGlobalBounds().intersects(playerBounds)) {
            if (tile.getFillColor() == sf::Color::Cyan) {
                return true;
            }
        }
    }
    return false;
}

