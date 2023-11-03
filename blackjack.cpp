#include <iostream>
#include <ctime>
#include <algorithm>

class Deck
{
    public:
        Deck();
        int* getCards();
        void shuffleDeck();
        void printCards();
    private:
        int cards[52];
};

int main()
{
    srand(time(0));
    Deck deck;
    int* cards = deck.getCards();
    deck.shuffleDeck();
    deck.printCards();
    deck.shuffleDeck();
    deck.printCards();
    deck.shuffleDeck();
    deck.printCards();

    int pCards;
};

Deck::Deck()
{
    for(int i = 0; i < 52; ++i)
    {
        cards[i] = i % 13 + 1;
    };
};

int* Deck::getCards()
{
    return cards;
}

void Deck::shuffleDeck()
{
    for(int i = 0; i < 52; i++)
    {
        int randomnumber = rand() % 52;
        std::swap(cards[i], cards[randomnumber]);
    }
    std::cout << "Shuffled deck" << std::endl; 
}

void Deck::printCards()
{
    for(int i = 0; i < 52; i++)
    {
        std::cout << cards[i] << ' ';
    };
    std::cout << std::endl;
}