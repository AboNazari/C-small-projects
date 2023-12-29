#ifndef WILDCARD_H
#define WILDCARD_H

#include "Card.h"

class WildCard : public Card {
private:
    bool isDrawFour;
    CardColor chosenColor;  // Added to track the chosen color
public:
    WildCard(bool isDrawFour);

    std::string toString() const override;

    CardColor getColor() const override;

    void setChosenColor(CardColor color);  // Method to set the chosen color
    CardColor getChosenColor() const;      // Method to get the chosen color

    CardType getType() const override;

    bool canBePlayedOn(const std::shared_ptr<Card> &topCard, CardColor currentPlayColor) const override;

};

#endif // WILDCARD_H
