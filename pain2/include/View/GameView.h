#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "../Model/Player.h"
#include <list>
#include <memory>
#include <string>

class GameView {
public:
    // Updated to take a std::list to match the player's hand data structure
    void displayHand(const std::list<std::shared_ptr<Card>> &hand);

    // Get the player's choice of card to play
    int getPlayerChoice();

    // Display a generic message
    void displayMessage(const std::string &message);

    // Display the current top card on the discard pile
    void displayCurrentCard(const std::shared_ptr<Card> &card);
};

#endif // GAMEVIEW_H
