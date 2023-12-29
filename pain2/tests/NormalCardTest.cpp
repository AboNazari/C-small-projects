#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <catch2/catch.hpp>
#include "../include/Model/NormalCard.h"

TEST_CASE("NormalCard functionality", "[NormalCard]") {
    SECTION("Color and Number Initialization") {
        NormalCard card(CardColor::RED, 5);
        REQUIRE(card.getColor() == CardColor::RED);
        REQUIRE(card.getNumber() == 5);
    }

    SECTION("String Representation") {
        NormalCard card(CardColor::BLUE, 1);
        REQUIRE(card.toString() == "BLUE 1");
    }

    SECTION("Card Type") {
        NormalCard numberCard(CardColor::GREEN, 3);
        REQUIRE(numberCard.getType() == CardType::NUMBER);

        NormalCard skipCard(CardColor::YELLOW, 10);
        REQUIRE(skipCard.getType() == CardType::SKIP);

    }

    SECTION("Playability On Top Card") {
        NormalCard baseCard(CardColor::RED, 5);
        NormalCard sameColorCard(CardColor::RED, 3);
        NormalCard differentColorCard(CardColor::GREEN, 5);
        NormalCard nonMatchingCard(CardColor::YELLOW, 7);

        // Testing with NormalCard as top card
        REQUIRE(sameColorCard.canBePlayedOn(std::make_shared<NormalCard>(baseCard), CardColor::RED) == true);
        REQUIRE(differentColorCard.canBePlayedOn(std::make_shared<NormalCard>(baseCard), CardColor::RED) == true);
        REQUIRE(nonMatchingCard.canBePlayedOn(std::make_shared<NormalCard>(baseCard), CardColor::RED) == false);

    }

}
