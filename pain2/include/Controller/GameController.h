#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../Model/UnoGame.h"
#include "../View/GameView.h"

/**
 * Manages the interactions between the game model and the view.
 */
class GameController {
private:
    UnoGame game;  // The game logic model.
    GameView view;  // The view responsible for user interaction and display.

public:
    /**
     * Constructor for GameController.
     * @param numHumanPlayers The number of human players in the game.
     */
    GameController(int numHumanPlayers);

    /**
     * Starts and manages the main game loop.
     */
    void startGameLoop();
};

#endif // GAMECONTROLLER_H
