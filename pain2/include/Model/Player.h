#ifndef PLAYER_H
#define PLAYER_H

#include <list>
#include <memory>
#include "Card.h"
#include <string>

class Player {
protected:
    std::list<std::shared_ptr<Card>> hand;

public:
    virtual ~Player() = default;

    // Updated to include current play color as a parameter
    virtual std::shared_ptr<Card>
    playCard(int cardIndex, const std::shared_ptr<Card> &topCard, CardColor currentColor) = 0;

    void drawCard(std::shared_ptr<Card> card) {
        hand.push_back(card);
    }

    int getHandSize() const {
        return hand.size();
    }

    // Updated to include current play color as a parameter
    virtual int getFirstPlayableCardIndex(const std::shared_ptr<Card> &topCard, CardColor currentColor) const = 0;

    const std::list<std::shared_ptr<Card>> &getHand() const {
        return hand;
    }

    // Updated to include current play color as a parameter
    virtual bool canPlay(const std::shared_ptr<Card> &topCard, CardColor currentColor) const = 0;

    virtual void notifyTurnStart() = 0;

    virtual std::string getName() const = 0;
};

#endif // PLAYER_H
