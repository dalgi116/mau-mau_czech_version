#ifndef MAIN_HPP
#define MAIN_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <iostream>
#include <time.h>

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
        std::srand(static_cast<unsigned int>(time(nullptr)));
        std::shuffle(this->cards.begin(), this->cards.end(), std::default_random_engine(std::rand()));
    }
    DrawPile(int a, std::vector<Card> b) : Pile(a, b) {};
};

class DiscardPile : public Pile
{
public:
    void printLastCard()
    {
        std::cout << this->cards.back().type << " (" << this->cards.back().color << ")";
    }
};

class Hand : public Pile
{
public:
    void drawCards(int drawCount) {};
    void printCards()
    {
        for (auto card : this->cards)
            std::cout << card.type << " (" << card.color << ")\n";
    }
};

class Choices
{
public:
    int cardCount;
    std::string other;
    std::vector<Card> cards;

    void printChoices()
    {
        std::cout << "(1) " << this->other << "\n";
        if (cardCount > 0)
        {
            int i = 1;
            for (auto card : cards)
            {
                i++;
                std::cout << "(" << i << ") " << card.type << " (" << card.color << ")\n";
            }
        }
    }
};

#endif /* MAIN_HPP */