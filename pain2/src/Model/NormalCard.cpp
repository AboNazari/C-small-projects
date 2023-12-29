#include "../../include/Model/NormalCard.h"
#include "Model/WildCard.h"
#include <string>
#include <stdexcept>
#include <iostream>

// Constructor initializing the NormalCard with a color and a number
NormalCard::NormalCard(CardColor color, int number) : Card(number), color(color) {}

// Converts the card information into a readable string format
std::string NormalCard::toString() const {
    std::string colorStr;
    switch (color) {
        case CardColor::RED:
            colorStr = "RED";
            break;
        case CardColor::YELLOW:
            colorStr = "YELLOW";
            break;
        case CardColor::GREEN:
            colorStr = "GREEN";
            break;
        case CardColor::BLUE:
            colorStr = "BLUE";
            break;
        default:
            throw std::invalid_argument("Invalid card color"); // Exception for invalid color
    }

    return colorStr + " " + std::to_string(number); // Return color and number as string
}

// Returns the color of the NormalCard
CardColor NormalCard::getColor() const {
    return color; // Return the card's color
}

// Determines the type of the NormalCard based on its number
CardType NormalCard::getType() const {
    switch (number) {
        case 10:
            return CardType::SKIP;
        case 11:
            return CardType::REVERSE;
        case 12:
            return CardType::DRAW_TWO;
        default:
            return CardType::NUMBER; // Default to NUMBER if not a special action card
    }
}

// Determines if the NormalCard can be played on the current top card
bool NormalCard::canBePlayedOn(const std::shared_ptr<Card> &topCard, CardColor currentPlayColor) const {
    // Compare with currentPlayColor if topCard is a wild card
    if (auto topWildCard = std::dynamic_pointer_cast<WildCard>(topCard)) {
        return this->color == currentPlayColor; // Check if color matches the play color
    }

    // Normal comparison for non-wild cards
    auto topNormalCard = std::dynamic_pointer_cast<NormalCard>(topCard);
    if (topNormalCard) {
        // Check if either color or number matches the top card
        return this->color == topNormalCard->getColor() || this->number == topNormalCard->getNumber();
    }

    return false; // Return false if no match found
}
