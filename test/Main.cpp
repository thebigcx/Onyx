#include "ShooterGame.h"

#include <iostream>

void runShooterGame()
{
    ShooterGame game;
    game.run();
}

int main()
{
    int num;

    std::cout << "GAMES:\n";
    std::cout << "0 : Shooter Game (similar to Galaga)\n\n";
    std::cout << "Enter a game: ";
    std::cin >> num;

    switch (num)
    {
        case 0:
            runShooterGame();
            break;
        default:
            std::cout << "Invalid\n";
    };

    return 0;
}