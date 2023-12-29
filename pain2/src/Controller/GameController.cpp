#include "../../include/Controller/GameController.h"

/**
 * Initializes the GameController with the specified number of human players.
 * Sets up the game and view components.
 * @param numHumanPlayers The number of human players in the game.
 */
GameController::GameController(int numHumanPlayers) : game(numHumanPlayers) {}

/**
 * Runs the main game loop.
 * Handles player turns and game progression until the game ends.
 */
void GameController::startGameLoop() {
    game.startGame(); // Starts the game.

    while (!game.isGameOver()) {
        // Displays the current top card and the current player's hand.
        view.displayCurrentCard(game.getCurrentCard());
        view.displayHand(game.getCurrentPlayerHand());

        // Gets the player's choice of action and adjusts for 0-based indexing.
        int choice = view.getPlayerChoice() - 1;

        // If the choice is negative, the player draws a card.
        if (choice < 0) {
            game.currentPlayerDrawCard();
        } else {
            // Otherwise, the player attempts to play the chosen card.
            game.currentPlayerPlayCard(choice);
        }

        // Moves to the next player after the current player's turn is done.
        game.nextPlayer();
    }

    // Displays a message when the game is over.
    view.displayMessage("Game Over!");
}
