#include "../../include/Model/BotPlayer.h"
#include <iostream>
#include <stdexcept>

BotPlayer::BotPlayer(const std::string &name) : name(name) {}

std::shared_ptr<Card> BotPlayer::playCard(int cardIndex, const std::shared_ptr<Card> &topCard, CardColor currentColor) {
    // Validate cardIndex to avoid accessing out-of-bounds elements
    if (cardIndex < 0 || cardIndex >= hand.size()) {
        throw std::out_of_range("Card index is out of range.");
    }

    auto it = hand.begin();
    std::advance(it, cardIndex);

    // Check if the selected card can be played
    if ((*it)->canBePlayedOn(topCard, currentColor)) {
        auto playedCard = *it;
        hand.erase(it); // Remove the card from the hand
        return playedCard; // Return the played card
    }

    return nullptr; // No playable card found
}

bool BotPlayer::canPlay(const std::shared_ptr<Card> &topCard, CardColor currentColor) const {
    for (const auto &card: hand) {
        if (card->canBePlayedOn(topCard, currentColor)) {
            return true; // Found a playable card
        }
    }
    return false; // No playable card found
}

void BotPlayer::notifyTurnStart() {
    std::cout << "Bot player's turn." << std::endl;
    // Bot logic or notifications for the start of the turn can be expanded here
}

std::string BotPlayer::getName() const {
    return name;
}

int BotPlayer::getFirstPlayableCardIndex(const std::shared_ptr<Card> &topCard, CardColor currentColor) const {
    int index = 0;
    for (const auto &card: hand) {
        if (card->canBePlayedOn(topCard, currentColor)) {
            return index;
        }
        ++index;
    }
    return -1; // Indicates no playable card is found
}

int BotPlayer::chooseCardIndex(const std::shared_ptr<Card> &topCard, CardColor currentColor) {
    int index = 0;

    // Try to find a playable card in the hand
    for (const auto &card: hand) {
        if (card->canBePlayedOn(topCard, currentColor)) {
            return index;
        }
        ++index;
    }

    return -1; // Indicate drawing a card if no playable card is found
}
