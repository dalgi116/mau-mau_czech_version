#ifndef MAIN_HPP
#define MAIN_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <iostream>

class Card
{
public:
    std::string type;
    char color;
    Card (std::string t, char c) : type(t), color(c) {};
};

class Pile
{
public:
    std::vector<Card> cards;
    int count;
    void moveCards(int moveCount, Pile& moveTo)
    {
        if (moveCount > this->count)
            throw std::invalid_argument("Not enough cards.\n");
        
        for (int i = 0; i < moveCount; i++)
        {
            moveTo.cards.push_back(this->cards.back());
            this->cards.pop_back();
            moveTo.count ++;
            this->count --;
        }
    }
    void printInfo()
    {
        std::cout << "Count: " << this->count << "\n";
        for (auto a : this->cards)
            std::cout << "Type: " << a.type << ", Color: " << a.color << "\n";
    }
    Pile() : count(0) {};
    Pile(int a, std::vector<Card> b) : count(a), cards(b) {};
};

class DrawPile : public Pile
{
public:
    void shuffleCards()
    {
        std::random_device rd;
        std::default_random_engine rng(rd());
        std::shuffle(this->cards.begin(), this->cards.end(), rng);
    }
    DrawPile(int a, std::vector<Card> b) : Pile(a, b) {};
};

class DiscardPile : public Pile
{
public:
    void printLastCard() {};
};

class Hand : public Pile
{
public:
    void drawCards(int drawCount) {};
    void printCards() {};
};

#endif /* MAIN_HPP */