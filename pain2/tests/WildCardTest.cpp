#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "../include/Model/WildCard.h"
#include "../include/Model/NormalCard.h"

TEST_CASE("WildCard functionality", "[WildCard]") {
    SECTION("Initialization and Type Check") {
        WildCard wildCard(false);
        REQUIRE(wildCard.getType() == CardType::WILD);

        WildCard drawFourCard(true);
        REQUIRE(drawFourCard.getType() == CardType::WILD_DRAW_FOUR);
    }

    SECTION("Setting and Getting Chosen Color") {
        WildCard wildCard(false);
        wildCard.setChosenColor(CardColor::BLUE);
        REQUIRE(wildCard.getChosenColor() == CardColor::BLUE);
    }

    SECTION("String Representation") {
        WildCard wildCard(false);
        REQUIRE(wildCard.toString() == "Wild");

        WildCard drawFourCard(true);
        REQUIRE(drawFourCard.toString() == "Wild Draw Four");
    }

    SECTION("Playability On Any Card") {
        WildCard wildCard(false);
        std::shared_ptr<Card> topCard = std::make_shared<NormalCard>(CardColor::RED, 5);

        REQUIRE(wildCard.canBePlayedOn(topCard, CardColor::RED) == true);
    }

}
