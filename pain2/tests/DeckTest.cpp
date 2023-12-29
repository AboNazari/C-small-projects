#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "../include/Model/Deck.h"

TEST_CASE("Deck functionality", "[Deck]") {
    Deck deck;

    SECTION("Initial Deck Setup") {
        REQUIRE(deck.remainingCards() > 0); // Ensure the deck is initially populated
    }

    SECTION("Shuffle Deck") {
        // This is difficult to test due to the randomness,
        // but you could check that the deck still contains the same number of cards
        unsigned int preShuffleCount = deck.remainingCards();
        deck.shuffle();
        REQUIRE(deck.remainingCards() == preShuffleCount);
    }

    SECTION("Draw Card") {
        unsigned int preDrawCount = deck.remainingCards();
        auto card = deck.drawCard();
        REQUIRE(card != nullptr); // Ensure a card is drawn
        REQUIRE(deck.remainingCards() == preDrawCount - 1); // Ensure the count is decremented
    }

    SECTION("Reshuffle Deck") {
        // To test reshuffle, you might need to draw all cards first, then attempt reshuffle
        // Be aware that this test could be affected by the state from previous tests
    }

    SECTION("Add to Discarded Pile and Reshuffle") {
        auto card = deck.drawCard();
        deck.addToDiscarded(card);
    }

}
