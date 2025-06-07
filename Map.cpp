#include "Map.hpp"

Mapa::Mapa(){
    std::string line;
    int row = 0;
    tile.setSize({100.f,100.f});
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
        }
        ++row;
    }
}

sf::FloatRect Mapa::getWallBounds(){
    return Wall.getGlobalBounds();
}
void Mapa::draw(sf::RenderWindow& window){
    for(auto tile : tiles){
        window.draw(tile);
        //cout<<"Drawing tile"<<endl;
    }
}
