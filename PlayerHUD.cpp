#include "PlayerHUD.hpp"
#include <cmath>

PlayerHUD::PlayerHUD(int scale)
{
    levelText.setFont(font);
    levelText.setString('1');
    levelText.setCharacterSize(40.f);
    WindowScale = scale/60;
    if (!font.loadFromFile("ProjektPPO\\fonts\\font1.ttf"))
    {
        cerr << "Nie udalo sie wczytac czcionki!\n";
    }
    //----Pasek zycia----
    hpBarBackground.setFillColor(sf::Color(90, 90, 100));
    hpBarBackground.setOutlineColor(sf::Color(50, 50, 50));
    scaleObject(hpBarBackground);
    hpBarBackground.setSize(sf::Vector2f(300.0f, 25.0f));
    hpBarBackground.setOutlineThickness(3.0f);
    hpBarBackground.setPosition({10.0f, 10.0f});

    hpBarForeground.setFillColor(sf::Color::Red);
    scaleObject(hpBarForeground);
    hpBarForeground.setPosition({10.0f, 10.0f});
    //----Pasek EXP----
    expBarBackground.setFillColor(sf::Color(90, 90, 100));
    expBarBackground.setOutlineColor(sf::Color(50, 50, 50));
    scaleObject(expBarBackground);
    expBarBackground.setSize(sf::Vector2f(250.0f, 10.0f));
    expBarBackground.setOutlineThickness(3.0f);
    expBarBackground.setPosition({10.0f, 45.0f});

    expBarForeground.setFillColor(sf::Color::Green);
    scaleObject(expBarForeground);
    expBarForeground.setPosition({10.0f, 45.0f});

    levelText.setFillColor(sf::Color::White);
    levelText.setOutlineColor(sf::Color::Black);
    scaleObject(levelText);
    levelText.setOutlineThickness(3);
    levelText.setPosition({280.0f, 35.0f});

    //----Pasek Many----
    energyBarBackground.setFillColor(sf::Color(90, 90, 100));
    energyBarBackground.setOutlineColor(sf::Color(50, 50, 50));
    scaleObject(energyBarBackground);
    energyBarBackground.setSize(sf::Vector2f(250.0f, 10.0f));
    energyBarBackground.setOutlineThickness(3.0f);
    energyBarBackground.setPosition({10.0f, 65.0f});

    energyBarForeground.setFillColor(sf::Color::Yellow);
    scaleObject(energyBarForeground);
    energyBarForeground.setPosition({10.0f, 65.0f});
}

void PlayerHUD::update(const sf::RenderWindow& window, Hero& hero)
{
    hpBarForeground.setSize(sf::Vector2f(300.0f*(hero.getHp()/hero.getmaxHp()), 25.0f)); //update HUD zaleznie od obecnych poziomow zasobow gracza
    expBarForeground.setSize(sf::Vector2f(250.0f*(hero.getExp()/hero.getmaxExp()), 10.0f));
    energyBarForeground.setSize(sf::Vector2f(250.0f*(hero.getenergy()/hero.getmaxenergy()), 10.0f));
    levelText.setString(std::to_string(hero.getLevel()));
}

void PlayerHUD::draw(sf::RenderWindow& window)
{
    window.setView(window.getDefaultView());
    window.draw(hpBarBackground);
    window.draw(hpBarForeground);

    window.draw(expBarBackground);
    window.draw(expBarForeground);

    window.draw(energyBarBackground);
    window.draw(energyBarForeground);

    window.draw(levelText);
}

template<typename T>
void PlayerHUD::scaleObject(T& drawable){ //template skalujacy wszystkie obiekty do rysowania
    drawable.scale({static_cast<float>(WindowScale),static_cast<float>(WindowScale)});
}
