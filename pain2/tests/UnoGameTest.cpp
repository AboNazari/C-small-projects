#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "../include/Model/UnoGame.h"
#include "../include/Model/NormalCard.h"
#include "../include/Model/WildCard.h"

TEST_CASE("UnoGame functionality", "[UnoGame]") {
    // Mock Card instances and other setup if necessary

    SECTION("Initialization and Setup") {
        UnoGame game(2);  // Game with 2 players
        REQUIRE(!game.isGameOver());  // Game should not be over after initialization
        REQUIRE(game.getCurrentPlayerHand().size() == 7);  // Assuming each player starts with 7 cards
    }

    SECTION("Player Turn Management") {
        UnoGame game(2);
        int initialPlayerIndex = game.getCurrentPlayerIndex();  // Store the index of the first player
        game.nextPlayer();  // Advance to the next player
        REQUIRE(game.getCurrentPlayerIndex() != initialPlayerIndex);  // Ensure the player index has changed
    }

    SECTION("Card Play Mechanics") {
        UnoGame game(2);
        auto currentPlayerHand = game.getCurrentPlayerHand();
        if (!currentPlayerHand.empty()) {
            int cardIndex = 0;  // Assume the first card is playable for simplicity
            bool playSuccess = game.currentPlayerPlayCard(cardIndex);
            REQUIRE(playSuccess);  // Check if the card play was successful
            REQUIRE(game.getCurrentPlayerHand().size() == currentPlayerHand.size() - 1);  // Check if a card was played
        }
    }

}
