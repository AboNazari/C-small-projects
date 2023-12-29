#include "../../include/Model/UnoGame.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <random>
#include <array>

// Constructor for the UnoGame class
UnoGame::UnoGame(int numHumanPlayers)
        : currentPlayerIndex(0), playDirection(true), currentColor(CardColor::RED) {
    createPlayers(numHumanPlayers); // Create the required number of human players
    deck.shuffle(); // Shuffle the deck before starting the game

    // Deal 7 cards to each player
    for (auto &player: players) {
        for (int i = 0; i < 7; ++i) {
            player->drawCard(deck.drawCard());
        }
    }

    // Draw the initial card to start the game
    currentCard = deck.drawCard();

    // Handle the case where the initial card is a wild card
    if (currentCard->getType() == CardType::WILD || currentCard->getType() == CardType::WILD_DRAW_FOUR) {
        currentColor = chooseRandomColor();  // Choose a random color for the game start
        std::cout << "Initial wild card drawn. Starting color is set to " << colorToString(currentColor) << std::endl;
    }
}

// Creates the specified number of human players and fills the rest with bot players
void UnoGame::createPlayers(int numHumanPlayers) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

    // Create human players
    for (int i = 0; i < numHumanPlayers; ++i) {
        std::cout << "Enter name for Player " << (i + 1) << ": ";
        std::string name;
        std::getline(std::cin, name);
        players.push_back(std::make_shared<HumanPlayer>(name));
    }

    // Create bot players for remaining slots
    for (int i = numHumanPlayers; i < 10; ++i) {
        players.push_back(std::make_shared<BotPlayer>("Bot" + std::to_string(i + 1)));
    }
}

// Main game loop
void UnoGame::startGame() {
    // Continue playing until the game is over
    while (!isGameOver()) {
        auto currentPlayer = players[currentPlayerIndex];
        std::cout << "Current card: " << currentCard->toString() << std::endl;
        std::cout << "It's " << currentPlayer->getName() << "'s turn." << std::endl;

        // Display the hand of the current player
        displayPlayerHand(currentPlayer);

        // Check if the current player can play any card
        if (!currentPlayer->canPlay(currentCard, currentColor)) {
            std::cout << "No playable card. Drawing a card..." << std::endl;
            currentPlayerDrawCard();
        } else {
            // Get the card index to play from the current player
            int cardIndex = -1;
            if (auto botPlayer = std::dynamic_pointer_cast<BotPlayer>(currentPlayer)) {
                // Bot player logic
                cardIndex = botPlayer->chooseCardIndex(currentCard, currentColor);
                if (cardIndex == -1) {
                    std::cout << "Bot draws a card..." << std::endl;
                    currentPlayerDrawCard();
                } else {
                    currentPlayerPlayCard(cardIndex);
                }
            } else {
                // Human player logic
                std::cout << "Choose a card index to play: ";
                std::cin >> cardIndex;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                // Validate the choice and prompt again if invalid
                while (!currentPlayerPlayCard(cardIndex)) {
                    std::cout << "Invalid card choice. Please choose another card." << std::endl;
                    std::cin >> cardIndex;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
        }

        // Move to the next player
        nextPlayer();
    }

    // Announce the game winner
    auto winner = std::find_if(players.begin(), players.end(),
                               [](const std::shared_ptr<Player> &player) {
                                   return player->getHandSize() == 0;
                               });

    if (winner != players.end()) {
        std::cout << "Congratulations, " << (*winner)->getName() << " won!" << std::endl;
    } else {
        std::cout << "Game Over!" << std::endl;
    }
}

// Checks if the game is over
bool UnoGame::isGameOver() const {
    // The game is over if any player has zero cards left
    return std::any_of(players.begin(), players.end(),
                       [](const std::shared_ptr<Player> &player) {
                           return player->getHandSize() == 0;
                       });
}

//udpate this to not only check for cardIndex but for card color and symbol

bool UnoGame::currentPlayerPlayCard(int cardIndex) {
    auto currentPlayer = players[currentPlayerIndex];
    auto playedCard = currentPlayer->playCard(cardIndex, currentCard, currentColor);

    // Check if the played card can be legally played
    if (playedCard && playedCard->canBePlayedOn(currentCard, currentColor)) {
        std::cout << currentPlayer->getName() << " played " << playedCard->toString() << std::endl;

        // Add the current card to the discarded pile if it's not null
        if (currentCard) {
            deck.addToDiscarded(currentCard);
        }

        // Update the current card and apply its effect
        currentCard = playedCard;
        applyCardEffect(playedCard);

        // For wild cards, update the current color after applying the card effect
        if (playedCard->getType() == CardType::WILD || playedCard->getType() == CardType::WILD_DRAW_FOUR) {
            if (auto wildCard = std::dynamic_pointer_cast<WildCard>(playedCard)) {
                currentColor = wildCard->getChosenColor();
            }
        }

        return true;
    } else {
        std::cout << "Invalid card choice. Please choose another card." << std::endl;
    }

    return false;
}


void UnoGame::applyCardEffect(const std::shared_ptr<Card> &card) {
    CardType cardType = card->getType();

    switch (cardType) {
        case CardType::SKIP:
            nextPlayer();
            break;
        case CardType::REVERSE:
            reversePlayOrder();
            if (players.size() == 2) {
                nextPlayer();
            }
            break;
        case CardType::DRAW_TWO:
            nextPlayer();
            players[currentPlayerIndex]->drawCard(deck.drawCard());
            players[currentPlayerIndex]->drawCard(deck.drawCard());
            nextPlayer();
            break;
        case CardType::WILD:
        case CardType::WILD_DRAW_FOUR:
            // Determine the color chosen for the wild card
            CardColor chosenColor;
            if (auto humanPlayer = std::dynamic_pointer_cast<HumanPlayer>(players[currentPlayerIndex])) {
                chosenColor = chooseColor();  // Human player chooses the color
            } else {
                chosenColor = chooseRandomColor();  // Bot chooses the color randomly
            }
            std::cout << "Color chosen: " << colorToString(chosenColor) << std::endl;

            // Update the current color in play and set the chosen color on the wild card
            currentColor = chosenColor;
            if (auto wildCard = std::dynamic_pointer_cast<WildCard>(card)) {
                wildCard->setChosenColor(chosenColor);
            }

            if (cardType == CardType::WILD_DRAW_FOUR) {
                // Check if the player has no matching color card
                if (!currentPlayerHasMatchingColor()) {
                    nextPlayer();
                    for (int i = 0; i < 4; ++i) {
                        players[currentPlayerIndex]->drawCard(deck.drawCard());
                    }
                    nextPlayer();
                } else {
                    std::cout << "Cannot play Wild Draw Four - you have a matching color card." << std::endl;
                }
            }
            break;
        default:
            break;
    }
}


void UnoGame::reshuffleDiscardedIntoDeck() {
    deck.reshuffle();
}

void UnoGame::currentPlayerDrawCard() {
    if (deck.remainingCards() == 0) {
        reshuffleDiscardedIntoDeck();
    }

    std::shared_ptr<Card> drawnCard = deck.drawCard();
    players[currentPlayerIndex]->drawCard(drawnCard);
    std::cout << "Drawn card: " << drawnCard->toString() << std::endl;
}

CardColor UnoGame::chooseColor() {
    // Function to prompt the current player to choose a color
    // This could be a simple console input in a text-based game
    std::cout << "Choose a color (RED, YELLOW, GREEN, BLUE): ";
    std::string colorInput;
    std::cin >> colorInput;

    if (colorInput == "RED" || colorInput == "red" || colorInput == "Red") return CardColor::RED;
    if (colorInput == "YELLOW" || colorInput == "yellow" || colorInput == "Yellow") return CardColor::YELLOW;
    if (colorInput == "GREEN" || colorInput == "Green" || colorInput == "green") return CardColor::GREEN;
    if (colorInput == "BLUE" || colorInput == "Blue" || colorInput == "blue") return CardColor::BLUE;

    // Default or error handling
    std::cout << "Invalid color. Defaulting to RED." << std::endl;
    return CardColor::RED;
}

CardColor UnoGame::chooseRandomColor() {
    static const std::array<CardColor, 4> colors = {CardColor::RED, CardColor::YELLOW, CardColor::GREEN,
                                                    CardColor::BLUE};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, colors.size() - 1);
    return colors[distrib(gen)];
}

void UnoGame::displayPlayerHand(const std::shared_ptr<Player> &player) {
    if (auto humanPlayer = std::dynamic_pointer_cast<HumanPlayer>(player)) {
        const auto &hand = humanPlayer->getHand();
        std::cout << humanPlayer->getName() << "'s hand: ";
        for (const auto &card: hand) {
            std::cout << card->toString() << ", ";
        }
        std::cout << std::endl;
    }
}

bool UnoGame::currentPlayerHasMatchingColor() {
    // Check if the current player has a card that matches the color of the top card
    auto currentHand = players[currentPlayerIndex]->getHand();
    for (const auto &card: currentHand) {
        if (card->getColor() == currentCard->getColor()) {
            return true;
        }
    }
    return false;
}

void UnoGame::nextPlayer() {
    currentPlayerIndex = (currentPlayerIndex + (playDirection ? 1 : -1) + players.size()) % players.size();
}

void UnoGame::reversePlayOrder() {
    playDirection = !playDirection;
    if (players.size() > 2) {
        currentPlayerIndex = (currentPlayerIndex + (playDirection ? 1 : -1) + players.size()) % players.size();
    }
}

const std::list<std::shared_ptr<Card>> &UnoGame::getCurrentPlayerHand() const {
    return players[currentPlayerIndex]->getHand();
}

const std::shared_ptr<Card> &UnoGame::getCurrentCard() const {
    return currentCard;
}

std::string UnoGame::colorToString(CardColor color) const {
    switch (color) {
        case CardColor::RED:
            return "RED";
        case CardColor::YELLOW:
            return "YELLOW";
        case CardColor::GREEN:
            return "GREEN";
        case CardColor::BLUE:
            return "BLUE";
        default:
            return "Unknown";
    }
}
