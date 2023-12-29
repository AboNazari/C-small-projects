#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"
#include <string>
#include <memory>

/**
 * Represents a human player in the UNO game.
 */
class HumanPlayer : public Player {
private:
    std::string name;

public:
    explicit HumanPlayer(const std::string &name);

    std::shared_ptr<Card>
    playCard(int cardIndex, const std::shared_ptr<Card> &topCard, CardColor currentColor) override;

    bool canPlay(const std::shared_ptr<Card> &topCard, CardColor currentColor) const override;

    int getFirstPlayableCardIndex(const std::shared_ptr<Card> &topCard, CardColor currentColor) const override;

    void notifyTurnStart() override;

    std::string getName() const override;
};

#endif // HUMANPLAYER_H
