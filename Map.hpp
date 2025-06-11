#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class Mapa{
public:
    Mapa(int inputscale);
    void draw(sf::RenderWindow& window);
    bool isWall(sf::Vector2f position, float radius);
private:
    sf::Sprite tile;
    std::vector<sf::Sprite> tiles;
    sf::Sprite wall;
    std::vector<sf::Sprite> walls;
    sf::Texture texture;
};
#endif // MAP_HPP
