#include <iostream>
#include "main.hpp"

int main()
{
    std::vector<Card> allCards = {
        {"Under", 'H'},
        {"Ober", 'H'},
        {"King", 'H'},
        {"Ace", 'H'},
        {"VII", 'H'},
        {"VIII", 'H'},
        {"IX", 'H'},
        {"X", 'H'},
        
        {"Under", 'B'},
        {"Ober", 'B'},
        {"King", 'B'},
        {"Ace", 'B'},
        {"VII", 'B'},
        {"VIII", 'B'},
        {"IX", 'B'},
        {"X", 'B'},

        {"Under", 'A'},
        {"Ober", 'A'},
        {"King", 'A'},
        {"Ace", 'A'},
        {"VII", 'A'},
        {"VIII", 'A'},
        {"IX", 'A'},
        {"X", 'A'},

        {"Under", 'L'},
        {"Ober", 'L'},
        {"King", 'L'},
        {"Ace", 'L'},
        {"VII", 'L'},
        {"VIII", 'L'},
        {"IX", 'L'},
        {"X", 'L'},
    };

    DrawPile drawPile(32, allCards);
    DiscardPile discardPile;
    Hand playersHand, botsHand;



    std::cout << "Hello, let's play!\n";

    // prepare a game
    drawPile.shuffleCards();
    drawPile.moveCards(4, playersHand);
    drawPile.moveCards(4, botsHand);
    drawPile.moveCards(1, discardPile);

    return 0;
}