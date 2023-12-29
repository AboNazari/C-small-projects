#ifndef BOTPLAYER_H
#define BOTPLAYER_H

#include "Player.h"
#include "Card.h"
#include <string>
#include <memory>

/**
 * Represents a bot player in the UNO game.
 * Inherits from the Player class and implements additional bot-specific behavior.
 */
class BotPlayer : public Player {
private:
    std::string name;

public:
    /**
     * Constructor for BotPlayer.
     * @param name The name of the bot player.
     */
    BotPlayer(const std::string &name);

    /**
     * Plays a card from the bot's hand.
     * @param cardIndex Index of the card to play.
     * @param topCard The current top card on the play stack.
     * @param currentColor The current play color.
     * @return Shared pointer to the played card.
     * @throws std::out_of_range if cardIndex is invalid.
     */
    std::shared_ptr<Card>
    playCard(int cardIndex, const std::shared_ptr<Card> &topCard, CardColor currentColor) override;

    /**
     * Checks if the bot can play a card.
     * @param topCard The current top card on the play stack.
     * @param currentColor The current play color.
     * @return True if the bot can play, false otherwise.
     */
    bool canPlay(const std::shared_ptr<Card> &topCard, CardColor currentColor) const override;

    /**
     * Gets the index of the first playable card in the bot's hand.
     * @param topCard The current top card on the play stack.
     * @param currentColor The current play color.
     * @return Index of the first playable card, or -1 if none are playable.
     */
    int getFirstPlayableCardIndex(const std::shared_ptr<Card> &topCard, CardColor currentColor) const override;

    /**
     * Notifies the bot player that their turn has started.
     */
    void notifyTurnStart() override;

    /**
     * Gets the name of the bot player.
     * @return The bot player's name.
     */
    std::string getName() const override;

    /**
     * Chooses a card index to play based on the current card and color.
     * @param currentCard The current top card on the play stack.
     * @param currentColor The current play color.
     * @return Index of the chosen card.
     */
    int chooseCardIndex(const std::shared_ptr<Card> &currentCard, CardColor currentColor);
};

#endif // BOTPLAYER_H
