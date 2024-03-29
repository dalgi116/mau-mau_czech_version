#include <string>
#include <vector>

class Card
{
public:
    std::string type;
    char color;
};

class Pile
{
public:
    std::vector<Card> cards;
    int count;
    void moveCards(int moveCount, Pile moveTo) {};
};

class DrawPile : public Pile
{
    void shuffleCards() {};
};

class DiscardPile : public Pile
{
    void printLastCard() {};
};

class Hand : public Pile
{
    void drawCards(int drawCount) {};
    void printCards() {};
};