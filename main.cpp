#include "main.hpp"
#include <map>


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
    bool userWins = false, botWins = false;
    int VIIStack = 0;
    bool VIIUsed, aceUsed;

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
        if (discardPile.cards.back().type == "Ace")
            aceUsed = false;
        if (discardPile.cards.back().type == "VII")
        {
            VIIStack++;
            VIIUsed = false;
        }

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
                choices.getChoices(discardPile, usersHand, VIIStack, VIIUsed, aceUsed);

                while (1)
                {
                    choices.printChoices();
                    std::cout << ">> ";
                    
                    std::cin >> usersChoice;

                    if (std::cin.fail())
                    {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    else if (usersChoice > 0 && usersChoice <= choices.cardCount + 1)
                        break;

                    std::cout << "Invalid input. Try it again.\n\n";
                }
                
                // evaluates the users choice
                if (usersChoice == 1)
                {
                    if (choices.other == "Skip")
                        aceUsed = true;
                    else
                    {
                        // user draws cards
                        int drawCardsCount;
                        if (choices.other == "Draw a card")
                            drawCardsCount = 1;
                        else
                        {
                            drawCardsCount = std::stoi(choices.other.substr(5, 1));
                            VIIUsed = true;
                            VIIStack = 0;
                        }
                        drawPile.drawCards(drawCardsCount, usersHand, discardPile);
                    }
                }
                else
                {
                    // user plays a card
                    Card playedCard = choices.cards.at(usersChoice - 2);
                    usersHand.playCard(playedCard, discardPile, VIIStack, VIIUsed, aceUsed);
                    
                    // checks a victory
                    if (usersHand.count == 0)
                    {
                        userWins = true;
                        break;
                    }

                    if (playedCard.type == "Ober")
                    {
                        // asks a player to select a color
                        while (1)
                        {
                            std::cout << "Which color do you change to?\n";
                            std::cout << "(1) Hearts\n";
                            std::cout << "(2) Bells\n";
                            std::cout << "(3) Acorns\n";
                            std::cout << "(4) Leaves\n";
                            std::cout << ">> ";
                            
                            std::cin >> usersChoice;

                            if (std::cin.fail())
                            {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            }
                            else if (usersChoice > 0 && usersChoice < 5)
                                break;

                            std::cout << "Invalid input. Try it again.\n\n";
                        }

                        char color;
                        switch (usersChoice)
                        {
                        case 1:
                            color = 'H';
                            break;
                        case 2:
                            color = 'B';
                            break;
                        case 3:
                            color = 'A';
                            break;
                        case 4:
                            color = 'L';
                            break;
                        }
                        discardPile.cards.back().color = color;
                    }
                }
            }
            else
            {
                // BOTS TURN

                choices.getChoices(discardPile, botsHand, VIIStack, VIIUsed, aceUsed);
                if (choices.cardCount > 0)
                {
                    // bot plays a card
                    Card playedCard = choices.cards.at(0);
                    botsHand.playCard(playedCard, discardPile, VIIStack, VIIUsed, aceUsed);

                    // checks a victory
                    if (botsHand.count == 0)
                    {
                        botWins = true;
                        break;
                    }

                    if (playedCard.type == "Ober")
                    {
                        // gets the most represented color in the hand
                        std::map<char, int> colors;
                        colors['H'] = 0, colors['B'] = 0, colors['A'] = 0, colors['L'] = 0;

                        for (auto card : botsHand.cards)
                        {
                            for (auto& color : colors)
                            {
                                if (card.color == color.first)
                                    color.second++;
                            }
                        }
                        int highestCount = 0;
                        char mostRepresentedColor;
                        for (auto color : colors)
                        {
                            if (color.second > highestCount)
                            {
                                highestCount = color.second;
                                mostRepresentedColor = color.first;
                            }
                            std::cout << "Color " << color.first << ", " << color.second << "\n";
                        }
                        std::cout << "Most represented color: " << mostRepresentedColor << "\n";
                        discardPile.cards.back().color = mostRepresentedColor;
                    }

                }
                else if (choices.other == "Skip")
                    aceUsed = true;
                else
                {
                    // bot draws cards
                    int drawCardsCount;
                    if (choices.other == "Draw a card")
                        drawCardsCount = 1;
                    else
                    {
                        drawCardsCount = std::stoi(choices.other.substr(5, 1));
                        VIIUsed = true;
                        VIIStack = 0;
                    }
                    drawPile.drawCards(drawCardsCount, botsHand, discardPile);
                }
            }
            activePlayer = !activePlayer;
        }

        // victory announcment
        if (userWins == true)
        {
            std::cout << "\nYou won!\n";
            std::cout << "Congratulations.\n\n";
        }
        else if (botWins == true)
        {
            std::cout << "\nBot wins...\n";
            std::cout << "Maybe next time.\n\n";
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

        // deletes old game
        usersHand.moveCards(usersHand.count, drawPile);
        botsHand.moveCards(botsHand.count, drawPile);
        discardPile.moveCards(discardPile.count, drawPile);
        VIIStack = 0;
        VIIUsed = false;
        aceUsed = false;
    }

    std::cout << "\nGoodbye...\n";

    return 0;
}