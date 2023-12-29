#ifndef NORMALCARD_H
#define NORMALCARD_H

#include "Card.h"

/**
 * Represents a normal card in the UNO game, with a color and a number.
 */
class NormalCard : public Card {
private:
    CardColor color; // The color of the card (Red, Yellow, Green, Blue)

public:
    /**
     * Constructs a NormalCard with a specified color and number.
     * @param color The color of the card.
     * @param number The number on the card.
     */
    NormalCard(CardColor color, int number);

    /**
     * Returns a string representation of the card, including its color and number.
     * @return A string representing the card.
     */
    std::string toString() const override;

    /**
     * Gets the color of this card.
     * @return The color of the card.
     */
    CardColor getColor() const override;

    /**
     * Gets the type of this card, which is NUMBER for NormalCard.
     * @return The CardType::NUMBER.
     */
    CardType getType() const override;

    /**
     * Determines if this card can be played on top of the given card.
     * @param topCard The current top card on the play pile.
     * @param currentPlayColor The current play color.
     * @return True if the card can be played, false otherwise.
     */
    bool canBePlayedOn(const std::shared_ptr<Card> &topCard, CardColor currentPlayColor) const override;
};

#endif // NORMALCARD_H
