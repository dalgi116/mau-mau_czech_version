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

    int usersChoice;

    DrawPile drawPile(32, allCards);
    DiscardPile discardPile;
    Hand playersHand, botsHand;


    std::cout << "Hello, let's play!\n";
    
    while (1)
    {
        // prepare a game
        drawPile.shuffleCards();
        drawPile.moveCards(4, playersHand);
        drawPile.moveCards(4, botsHand);
        drawPile.moveCards(1, discardPile);

        // decides if the player wants to play another game
        while (1)
        {
            std::cout << "Do you want to play again?\n";
            std::cout << "(1) YES\n";
            std::cout << "(2) NO\n";
            std::cout << ">> ";
            
            std::cin >> usersChoice;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else if (usersChoice == 1 || usersChoice == 2)
                break;

            std::cout << "Invalid input. Try it again.\n\n";
        }
        if (usersChoice == 2)
            break;
    }

    std::cout << "\nGoodbye...\n";

    return 0;
}