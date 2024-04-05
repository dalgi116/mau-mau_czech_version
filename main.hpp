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
    void drawCards(int moveCount, Pile& moveTo, Pile& moveFromToShuffle)
    {
        if (this->count < moveCount)
        {
            Card topCard = moveFromToShuffle.cards.back();
            moveFromToShuffle.cards.pop_back();
            moveFromToShuffle.moveCards(moveFromToShuffle.count, *this);
            moveFromToShuffle.cards.push_back(topCard);
            moveFromToShuffle.count++;
        }
        moveCards(moveCount, moveTo);
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
    void playCard(Card& card, Pile& pile)
    {
        pile.cards.push_back(card);
        pile.count++;
        int i = 0;
        for (auto a : this->cards)
        {
            if (a.color == card.color && a.type == card.type)
                break;
            i++;
        }
        this->cards.erase(this->cards.begin() + i);
        this->count--;
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
    void getChoices(const Pile& statement, const Pile& object)
    {
        std::string statementType = statement.cards.back().type;
        char statementColor = statement.cards.back().color;
        
        this->cardCount = 0;
        this->cards.clear();

        if (statementType == "Ace")
        {
            this->other = "Skip";
            bool hasAce = 0;
            for (auto card : object.cards)
            {
                if (card.type == "Ace")
                    hasAce = 1;
            }
            if (hasAce == 0)
                return;
        }
        else if (statementType == "VII")
        {
            this->other = "Draw 2 cards";
            bool hasVII = 0;
            for (auto card : object.cards)
            {
                if (card.type == "VII")
                    hasVII = 1;
            }
            if (hasVII == 0)
                return;
        }

        if (statementType != "Ace" && statementType != "VII")
            this->other = "Draw a card";
        
        for (auto card : object.cards)
        {
            if (card.type == "Ober" || card.type == statementType || card.color == statementColor)
            {
                this->cardCount++;
                this->cards.push_back(card);
            }
        }
    }
};

#endif /* MAIN_HPP */