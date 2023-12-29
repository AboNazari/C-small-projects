#include "../../include/View/GameView.h"
#include <iostream>

void GameView::displayHand(const std::list<std::shared_ptr<Card>> &hand) {
    int index = 0;
    for (const auto &card: hand) {
        std::cout << index++ << ": " << card->toString() << std::endl;
    }
}

int GameView::getPlayerChoice() {
    std::cout << "Enter the index of the card you want to play: ";
    int choice;
    std::cin >> choice;
    return choice;
}

void GameView::displayMessage(const std::string &message) {
    std::cout << message << std::endl;
}

void GameView::displayCurrentCard(const std::shared_ptr<Card> &card) {
    if (card) {
        std::cout << "Current card: " << card->toString() << std::endl;
    } else {
        std::cout << "No current card." << std::endl;
    }
}
