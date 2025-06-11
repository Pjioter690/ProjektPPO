#include "Map.hpp"

Mapa::Mapa(int inputscale){
    float scaleFactor = static_cast<float>(inputscale) / 240.f;
    std::string line;
    int row = 0;
    std::ifstream file("ProjektPPO\\maps\\map1.txt");
    if (!file) {
        cerr<< "Nie mozna otworzyc pliku\n";
    }
    if (!texture.loadFromFile("ProjektPPO\\textures\\sciana_podloga.png"))
        cerr << "Nie udalo sie wczytac tekstury sciana_podloga!\n";
    tile.setTexture(texture);
    wall.setTexture(texture);
    tile.scale({scaleFactor,scaleFactor});
    wall.scale({scaleFactor,scaleFactor});

    while (std::getline(file, line)) {
        for (std::size_t col = 0; col < line.size(); ++col) {
            float posX = col * 400.f * scaleFactor;
            float posY = row * 400.f * scaleFactor;
            if (line[col] == '1') {
                tile.setTextureRect(sf::IntRect(400,0,400,400));
                tile.setPosition(posX,posY);
                tiles.push_back(tile);
            }
            else if (line[col] == '0') {
                wall.setTextureRect(sf::IntRect(0,0,400,400));
                wall.setPosition(posX,posY);
                walls.push_back(wall);
            }
        }
        ++row;
    }
}
void Mapa::draw(sf::RenderWindow& window){
    for(auto tile : tiles){
        window.draw(tile);
    }
    for(auto wall : walls){
        window.draw(wall);
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
    for (const auto& wall : walls) {
        if (wall.getGlobalBounds().intersects(playerBounds)) {
            return true;
        }
    }
    return false;
}

