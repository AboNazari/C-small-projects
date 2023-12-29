#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "../include/Model/BotPlayer.h"
#include "../include/Model/NormalCard.h"  // Assuming you have NormalCard for testing
#include <memory>

TEST_CASE("BotPlayer functionality", "[BotPlayer]") {
    BotPlayer bot("Bot");

    SECTION("Initialization and Name") {
        REQUIRE(bot.getName() == "Bot");
    }

    SECTION("Play Card with Empty Hand") {
        std::shared_ptr<Card> topCard = std::make_shared<NormalCard>(CardColor::RED, 5);

        REQUIRE_THROWS_AS(bot.playCard(0, topCard, CardColor::RED), std::out_of_range);
    }

    SECTION("Can Play Check with Empty Hand") {
        std::shared_ptr<Card> topCard = std::make_shared<NormalCard>(CardColor::RED, 5);

        REQUIRE(bot.canPlay(topCard, CardColor::RED) == false);
    }

    SECTION("Get First Playable Card Index with Empty Hand") {
        std::shared_ptr<Card> topCard = std::make_shared<NormalCard>(CardColor::RED, 5);

        REQUIRE(bot.getFirstPlayableCardIndex(topCard, CardColor::RED) == -1);
    }

}
