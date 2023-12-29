#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "../include/Model/HumanPlayer.h"
#include "../include/Model/NormalCard.h"  // Assuming you have NormalCard for testing

TEST_CASE("HumanPlayer functionality", "[HumanPlayer]") {
    HumanPlayer player("Alice");

    SECTION("Initialization and Name") {
        REQUIRE(player.getName() == "Alice");
    }

    SECTION("Play Card with Empty Hand") {
        std::shared_ptr<Card> topCard = std::make_shared<NormalCard>(CardColor::RED, 5);

        // Expecting nullptr since the hand is empty
        REQUIRE(player.playCard(0, topCard, CardColor::RED) == nullptr);
    }

    SECTION("Can Play Check with Empty Hand") {
        std::shared_ptr<Card> topCard = std::make_shared<NormalCard>(CardColor::RED, 5);

        REQUIRE(player.canPlay(topCard, CardColor::RED) == false);
    }

    SECTION("Get First Playable Card Index with Empty Hand") {
        std::shared_ptr<Card> topCard = std::make_shared<NormalCard>(CardColor::RED, 5);

        // Since automatic selection is not applicable for human players, expecting -1
        REQUIRE(player.getFirstPlayableCardIndex(topCard, CardColor::RED) == -1);
    }

}
