#ifndef DECK_H
#define DECK_H

#include <stack>
#include <memory>
#include <vector>
#include "Card.h"
#include "NormalCard.h"
#include "WildCard.h"

/**
 * Represents the deck of cards in the UNO game.
 */
class Deck {
private:
    std::stack<std::shared_ptr<Card>> cards;
    std::vector<std::shared_ptr<Card>> discardedPile;

public:
    Deck();

    void shuffle();

    std::shared_ptr<Card> drawCard();

    unsigned int remainingCards() const;

    void reshuffle();

    void addToDiscarded(const std::shared_ptr<Card> &card);

private:
    void addNumberCards();

    void addActionCards();

    void addWildCards();
};

#endif // DECK_H
