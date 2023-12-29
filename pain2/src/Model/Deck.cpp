#include "../../include/Model/Deck.h"
#include <algorithm>
#include <random>
#include <vector>
#include <stdexcept>

Deck::Deck() {
    addNumberCards();   // Adds number cards to the deck
    addActionCards();   // Adds action cards to the deck
    addWildCards();     // Adds wild cards to the deck
    shuffle();          // Shuffles the deck
}

void Deck::shuffle() {
    std::vector<std::shared_ptr<Card>> tempVector; // Temporary vector to hold cards for shuffling

    // Move cards from stack to vector
    while (!cards.empty()) {
        tempVector.push_back(std::move(cards.top()));
        cards.pop();
    }

    // Shuffle the vector
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(tempVector.begin(), tempVector.end(), g);

    // Move shuffled cards back to stack
    for (auto &card: tempVector) {
        cards.push(std::move(card));
    }
}

void Deck::reshuffle() {
    if (discardedPile.empty()) {
        throw std::runtime_error("No discarded cards to reshuffle."); // Error if no cards to reshuffle
    }

    // Move discarded cards back to the deck
    for (auto &card: discardedPile) {
        cards.push(std::move(card));
    }
    discardedPile.clear();

    shuffle(); // Shuffle the deck again
}

void Deck::addToDiscarded(const std::shared_ptr<Card> &card) {
    discardedPile.push_back(card); // Add card to the discarded pile
}

std::shared_ptr<Card> Deck::drawCard() {
    if (cards.empty()) {
        if (discardedPile.empty()) {
            throw std::runtime_error(
                    "Attempted to draw from an empty deck and discard pile."); // Error if deck is empty
        }
        reshuffle(); // Reshuffle if deck is empty but there are discarded cards
    }
    auto card = cards.top();
    cards.pop();
    return card; // Return the top card
}

unsigned int Deck::remainingCards() const {
    return cards.size(); // Return the number of remaining cards in the deck
}

void Deck::addNumberCards() {
    // Add number cards for each color
    for (int color = static_cast<int>(CardColor::RED); color <= static_cast<int>(CardColor::BLUE); ++color) {
        for (int number = 0; number <= 9; ++number) {
            cards.push(std::make_shared<NormalCard>(static_cast<CardColor>(color), number));
            if (number != 0) { // Add two of each card, except for 0
                cards.push(std::make_shared<NormalCard>(static_cast<CardColor>(color), number));
            }
        }
    }
}

void Deck::addActionCards() {
    // Add action cards for each color
    for (int color = static_cast<int>(CardColor::RED); color <= static_cast<int>(CardColor::BLUE); ++color) {
        for (int i = 0; i < 2; ++i) { // Two of each action card per color
            cards.push(std::make_shared<NormalCard>(static_cast<CardColor>(color), 10)); // Skip
            cards.push(std::make_shared<NormalCard>(static_cast<CardColor>(color), 11)); // Reverse
            cards.push(std::make_shared<NormalCard>(static_cast<CardColor>(color), 12)); // Draw Two
        }
    }
}

void Deck::addWildCards() {
    // Add wild cards
    for (int i = 0; i < 4; ++i) { // Four of each wild card
        cards.push(std::make_shared<WildCard>(false)); // Regular Wild
        cards.push(std::make_shared<WildCard>(true));  // Wild Draw Four
    }
}
