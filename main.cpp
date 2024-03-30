#include "main.hpp"


bool whoStarts(const int& roundNum, const bool& startingPlayer)
{
    if (roundNum > 0)
        return !startingPlayer;
    else
    {
        std::srand(static_cast<unsigned int>(time(nullptr)));
        return std::rand() % 2;
    }
}

void getChoices(const Pile& statement, const Pile& object, Choices& choices)
{
    std::string statementType = statement.cards.back().type;
    char statementColor = statement.cards.back().color;
    
    choices.cardCount = 0;
    choices.cards.clear();

    if (statementType == "Ace")
    {
        bool hasAce = 0;
        for (auto card : object.cards)
        {
            if (card.type == "Ace")
                hasAce = 1;
        }
        if (hasAce == 0)
        {
            choices.other = "Skip";
            return;
        }
    }
    else if (statementType == "VII")
    {
        bool hasVII = 0;
        for (auto card : object.cards)
        {
            if (card.type == "VII")
                hasVII = 1;
        }
        if (hasVII == 0)
        {
            choices.other = "Draw 2 cards";
            return;
        }
    }

    choices.other = "Draw a card";
    
    for (auto card : object.cards)
    {
        if (card.type == "Ober" || card.type == statementType || card.color == statementColor)
        {
            choices.cardCount++;
            choices.cards.push_back(card);
        }
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
    int roundNum = 0;
    bool startingPlayer; // 0-user, 1-bot
    bool activePlayer;
    int choiceCount;

    DrawPile drawPile(32, allCards);
    DiscardPile discardPile;
    Hand usersHand, botsHand;
    Choices choices;


    std::cout << "Hello, let's play!\n\n";
    
    while (1)
    {
        // prepares a game
        drawPile.shuffleCards();
        drawPile.moveCards(4, usersHand);
        drawPile.moveCards(4, botsHand);
        drawPile.moveCards(1, discardPile);

        startingPlayer = whoStarts(roundNum, startingPlayer);
        activePlayer = startingPlayer;
        std::cout << "Starting player: " << ((startingPlayer) ? "Bot" : "User") << "\n";

        while (1)
        {
            if (activePlayer == 0)
            {
                //  USERS TURN

                // prints board data
                std::cout << "\nOponents hand:\t" << botsHand.count << " cards\n";
                std::cout << "Discard pile:\t";
                discardPile.printLastCard();
                std::cout << "\n";
                std::cout << "Your cards:\n";
                usersHand.printCards();

                // prints choices and lets user to decide
                std::cout << "What will you play?\n";
                getChoices(discardPile, usersHand, choices);
                choices.printChoices();
                std::cout << ">> ";
            }
            else
            {
                // BOTS TURN

            }
            activePlayer = !activePlayer;
        }


        // decides if the user wants to play again
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