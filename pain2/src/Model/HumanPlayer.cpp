#include "../../include/Model/HumanPlayer.h"
#include <iostream>
#include <stdexcept>

HumanPlayer::HumanPlayer(const std::string &name) : name(name) {}

std::shared_ptr<Card>
HumanPlayer::playCard(int cardIndex, const std::shared_ptr<Card> &topCard, CardColor currentColor) {
    // Validate card index
    if (cardIndex >= 0 && cardIndex < getHandSize()) {
        auto it = std::next(hand.begin(), cardIndex);
        auto chosenCard = *it;

        // Check if the chosen card can be played
        if (chosenCard->canBePlayedOn(topCard, currentColor)) {
            hand.erase(it); // Remove the card from hand
            return chosenCard; // Return the chosen card
        } else {
            std::cout << "You cannot play this card." << std::endl;
        }
    } else {
        std::cout << "Invalid card index." << std::endl;
        // Optionally, you can throw an exception here
        // throw std::invalid_argument("Invalid card index.");
    }
    return nullptr; // Return null if card cannot be played or index is invalid
}

int HumanPlayer::getFirstPlayableCardIndex(const std::shared_ptr<Card> &topCard, CardColor currentColor) const {
    // For human players, automatic card selection is not applicable
    return -1;
}

bool HumanPlayer::canPlay(const std::shared_ptr<Card> &topCard, CardColor currentColor) const {
    for (const auto &card: hand) {
        if (card->canBePlayedOn(topCard, currentColor)) {
            return true; // Return true if a playable card is found
        }
    }
    return false; // Return false if no playable cards are found
}

void HumanPlayer::notifyTurnStart() {
    std::cout << "Your turn. Please choose a card to play or draw." << std::endl;
    // Additional logic or UI interactions for human players can be implemented here
}

std::string HumanPlayer::getName() const {
    return name; // Return the player's name
}
