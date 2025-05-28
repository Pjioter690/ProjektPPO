#include <SFML/Graphics.hpp>
#include <iostream>
#include<windows.h>
using namespace std;
#include "GameClass.hpp"

int main()
{
#ifdef _WIN32
    SetProcessDPIAware();
#endif
    Game game;
    game.run();
    return 0;
}
