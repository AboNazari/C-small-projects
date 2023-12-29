#include "../../include/Model/WildCard.h"

// Constructor initializing the WildCard with a flag indicating if it's a Draw Four card
WildCard::WildCard(bool isDrawFour)
        : Card(-1), isDrawFour(isDrawFour), chosenColor(CardColor::WILD) {}

// Sets the color chosen for the wild card
void WildCard::setChosenColor(CardColor color) {
    chosenColor = color; // Set the chosen color for the wild card
}

// Returns the color chosen for the wild card
CardColor WildCard::getChosenColor() const {
    return chosenColor; // Return the chosen color
}

// Returns the current color of the wild card
CardColor WildCard::getColor() const {
    return chosenColor; // Return the current color of the wild card
}

// Converts the wild card information into a readable string format
std::string WildCard::toString() const {
    return isDrawFour ? "Wild Draw Four" : "Wild"; // String representation of the wild card
}

// Returns the type of the WildCard (Wild or Wild Draw Four)
CardType WildCard::getType() const {
    return isDrawFour ? CardType::WILD_DRAW_FOUR : CardType::WILD; // Return the type of wild card
}

// Determines if the WildCard can be played on the current top card
bool WildCard::canBePlayedOn(const std::shared_ptr<Card> &topCard, CardColor currentPlayColor) const {
    return true; // Wild cards can be played on any card
}
