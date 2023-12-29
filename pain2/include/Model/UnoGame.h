#ifndef UNOGAME_H
#define UNOGAME_H

#include "Deck.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "BotPlayer.h"
#include <memory>
#include <vector>
#include <string>
#include <array>
#include <random>

// The UnoGame class encapsulates all the logic for playing a game of Uno.
class UnoGame {
private:
    Deck deck;  // Represents the deck of Uno cards.
    std::vector<std::shared_ptr<Player>> players;  // Stores all players in the game.
    CardColor currentColor;  // The current color in play, used for wild cards.

    std::shared_ptr<Card> currentCard;  // The current top card on the play pile.
    int currentPlayerIndex;  // Index of the current player in the players vector.
    bool playDirection;  // Indicates the direction of play (true for normal, false for reverse).

    // Method to create human and bot players.
    void createPlayers(int numHumanPlayers);

    // Applies the effect of the card played (e.g., skip, reverse, draw two).
    void applyCardEffect(const std::shared_ptr<Card> &card);

    // Displays the hand of the given player.
    void displayPlayerHand(const std::shared_ptr<Player> &player);


    // Randomly chooses a color, used when bots play a wild card.
    CardColor chooseRandomColor();

    static CardColor chooseColor();

    // Checks if the current player has a card matching the current color.
    bool currentPlayerHasMatchingColor();

    // Reverses the direction of play.
    void reversePlayOrder();

public:
    // Constructor: sets up the game with the given number of human players.
    UnoGame(int numHumanPlayers);


    // Advances the game to the next player.
    void nextPlayer();

    // Method to handle a player attempting to play a card.
    bool currentPlayerPlayCard(int cardIndex);

    // Starts and manages the main game loop.
    void startGame();

    // Checks if the game is over (i.e., if any player has no cards left).
    bool isGameOver() const;

    // Handles the current player drawing a card from the deck.
    void currentPlayerDrawCard();

    // Returns the hand of the current player.
    const std::list<std::shared_ptr<Card>> &getCurrentPlayerHand() const;

    // Returns the current card in play.
    const std::shared_ptr<Card> &getCurrentCard() const;

    // Reshuffles the discarded cards into the deck when it runs out of cards.
    void reshuffleDiscardedIntoDeck();

    virtual std::string colorToString(CardColor color) const;

};

#endif