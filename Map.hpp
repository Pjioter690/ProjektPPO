#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class Mapa{
public:
    Mapa();
    sf::FloatRect getWallBounds();
    void draw(sf::RenderWindow& window);
    std::vector<sf::RectangleShape> getTiles();
private:
    sf::RectangleShape tile;
    std::vector<sf::RectangleShape> tiles;
};


#endif // MAP_HPP
