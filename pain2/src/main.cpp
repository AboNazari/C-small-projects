#include "../include/Controller/GameController.h"
#include <iostream>


void displayWelcomeMessage() {
    std::cout << R"(
  _    _  _  _      __
 | |  | || \|  | ||    ||
 | |__| ||     | ||    ||
 |______||_|\__| || __ ||
)" << '\n';
    std::cout << "Welcome to Terminal UNO!" << std::endl;
    std::cout << "Get ready to match colors, numbers, and outsmart your opponents!" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

int main() {
    int numHumanPlayers;
    displayWelcomeMessage();
    std::cout << "Enter the number of human players: ";
    std::cin >> numHumanPlayers;

    // Check for valid input
    if (std::cin.fail() || numHumanPlayers < 1 || numHumanPlayers > 10) {
        std::cerr << "Invalid number of players. Please enter a number between 1 and 10." << std::endl;
        return 1; // Exit with an error code
    }

    GameController gameController(numHumanPlayers);
    gameController.startGameLoop();

    return 0;
}
