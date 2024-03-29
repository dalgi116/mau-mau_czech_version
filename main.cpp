#include "main.hpp"


int whoStarts(const int& roundNum, const bool& startingPlayer)
{
    if (roundNum > 0)
        return !startingPlayer;
    else
    {
        std::srand(static_cast<unsigned int>(time(nullptr)));
        int num = std::rand() % 2;
        return num;
    }
}

int main()
{
    std::vector<Card> allCards = {
        {"Under", 'H'}, {"Ober", 'H'}, {"King", 'H'}, {"Ace", 'H'}, {"VII", 'H'}, {"VIII", 'H'}, {"IX", 'H'}, {"X", 'H'},
        {"Under", 'B'}, {"Ober", 'B'}, {"King", 'B'}, {"Ace", 'B'}, {"VII", 'B'}, {"VIII", 'B'}, {"IX", 'B'}, {"X", 'B'},
        {"Under", 'A'}, {"Ober", 'A'}, {"King", 'A'}, {"Ace", 'A'}, {"VII", 'A'}, {"VIII", 'A'}, {"IX", 'A'}, {"X", 'A'},
        {"Under", 'L'}, {"Ober", 'L'}, {"King", 'L'}, {"Ace", 'L'}, {"VII", 'L'}, {"VIII", 'L'}, {"IX", 'L'}, {"X", 'L'}
    };

    int usersChoice;
    int roundNum;
    int startingPlayer = 0; // 0-user, 1-bot

    DrawPile drawPile(32, allCards);
    DiscardPile discardPile;
    Hand usersHand, botsHand;


    std::cout << "Hello, let's play!\n";
    
    while (1)
    {
        // prepare a game
        drawPile.shuffleCards();
        drawPile.moveCards(4, usersHand);
        drawPile.moveCards(4, botsHand);
        drawPile.moveCards(1, discardPile);

        startingPlayer = whoStarts(roundNum, startingPlayer);
        std::cout << "starting: " << startingPlayer << "\n";

        // decides if the user wants to play another game
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

        roundNum++;
    }

    std::cout << "\nGoodbye...\n";

    return 0;
}