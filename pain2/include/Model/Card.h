#ifndef CARD_H
#define CARD_H

#include <string>
#include <memory>

enum class CardColor {
    RED, YELLOW, GREEN, BLUE, WILD
};

enum class CardType {
    NUMBER, SKIP, REVERSE, DRAW_TWO, WILD, WILD_DRAW_FOUR
};

/**
 * Base class representing a card in the UNO game.
 */
class Card {
protected:
    int number;  // Numeric value for number cards, -1 for non-number cards

public:
    explicit Card(int number = -1) : number(number) {}

    virtual ~Card() = default;

    virtual std::string toString() const = 0;

    virtual CardColor getColor() const = 0;

    virtual CardType getType() const = 0;

    /**
     * Determines if this card can be played on top of another card.
     * @param topCard The card currently on top of the pile.
     * @param currentPlayColor The current play color.
     * @return True if playable, false otherwise.
     */
    virtual bool canBePlayedOn(const std::shared_ptr<Card> &topCard, CardColor currentPlayColor) const = 0;

    bool operator==(const Card &other) const;

    int getNumber() const { return number; }
};

#endif // CARD_H
