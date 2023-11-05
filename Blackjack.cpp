#include <iostream>
#include <vector>
#include <ctime>

class Deck
{
    public:
        Deck();
        int* getCards();
        void shuffle();
        void printCards();
        int drawCard();
    private:
        int cards[52];
};

int getTotal(std::vector<int> cards);
int pAceLogic();
int dAceLogic(int dTotal);

int main()
{
    srand(time(0));
    Deck deck;
    std::vector<int> pCards, dCards;
    bool playAgain = true;
    bool playerCanHit = true;
    bool bust = false;
    std::string playAgainInput;
    std::string playerInput;

    while(playAgain)
    {
        //title
        std::cout << "-=- BLACKJACK -=-\n\n";

        //shuffle
        deck.shuffle();

        //draw initial hands
        dCards.push_back(deck.drawCard());
        dCards.push_back(deck.drawCard());
        
        pCards.push_back(deck.drawCard());
        pCards.push_back(deck.drawCard());

        //initial text
        std::cout << "Dealer draws " << dCards[0] << " and another card\n\n";
        std::cout << "You draw " << pCards[0] << " and " << pCards[1] << std::endl;

        //initial aces
        if (pCards[0] == 1)
        {
            pCards[0] = pAceLogic();
        }
        if (pCards[1] == 1)
        {
            pCards[1] = pAceLogic();
        }
        if (dCards[0] == 1)
        {
            dCards[0] = dAceLogic(getTotal(dCards));
        }
        if (dCards[1] == 1)
        {
            dCards[1] = dAceLogic(getTotal(dCards));
        }
        
        //std::cout << "Player total: " << getTotal(pCards) << std::endl;

        //initial hand logic
        if(getTotal(pCards) == 22)
        {
            std::cout << "Bust!\n";
            playerCanHit = false;
        }
        if(getTotal(pCards) == 21)
        {
            std::cout << "You got Blackjack!\n";
            playerCanHit = false;
        }
        
        //player cards
        while(playerCanHit)
        {
            //prompt hit or stand
            do{
                std::cout << "Hit or Stand (h/s): ";
                std::cin >> playerInput;
            }while(playerInput != "h" && playerInput != "s");
            //hit
            if(playerInput == "h")
            {
                pCards.push_back(deck.drawCard());
                std::cout << "You draw " << pCards[pCards.size() - 1] << std::endl;
                if(pCards[pCards.size() - 1] == 1)
                {
                    pCards[pCards.size() - 1] = pAceLogic();
                }
                if(getTotal(pCards) > 21)
                {
                    std::cout << "Bust!\n\n";
                    playerCanHit = false;
                    bust = true;
                }
                if(getTotal(pCards) == 21)
                {
                    std::cout << "You got Blackjack!\n\n";
                    playerCanHit = false;
                }
            }
            //stand
            else
            {
                std::cout << "You stand.\n\n";
                playerCanHit = false;
            }
        }

        //dealer cards
        if (!bust)
        {
            std::cout << "Dealer drew " << dCards[0] << " and " << dCards[1] << std::endl;
            //dealer initial ace
            if(dCards[0] == 1)
            {
                dCards[0] = dAceLogic(getTotal(dCards));
            }
            while(getTotal(dCards) <= 16)
            {
                dCards.push_back(deck.drawCard());
                if(dCards[dCards.size() - 1] == 1)
                    {
                        dCards[dCards.size() - 1] = dAceLogic(getTotal(dCards));
                    }
                std::cout << "Dealer draws " << dCards[dCards.size() - 1] << std::endl;
            }
            if (getTotal(dCards) == 21)
            {
                std::cout << "Dealer got Blackjack!\n";
            }
            if (getTotal(dCards) > 21)
            {
                std::cout << "Dealer busts! You win!\n";
            }
            else
            {
                if (getTotal(dCards) == getTotal(pCards))
                {
                    std::cout << "Draw!\n\n";
                }
                else if (getTotal(dCards) < getTotal(pCards))
                {
                    std::cout << "You win!\n\n";
                }
                else
                {
                    std::cout << "You lose.\n\n";
                }
            }
        }
            
        //play again
        while(playAgainInput != "y" && playAgainInput != "n")
        {
            std::cout << "Play again? (y/n): ";
            std::cin >> playAgainInput;
        }
        if(playAgainInput == "n")
        {
            playAgain = false;
        }

        //reset everything
        playAgainInput = "";
        playerCanHit = true;
        bust = false;
        pCards.clear();
        dCards.clear();
        std::cout << "\n\n";
    }
}

Deck::Deck()
{
    for(int i = 0; i < 52; ++i)
    {
        cards[i] = i % 13 + 1;
    };
};

//getter for int* cards
int* Deck::getCards()
{
    return cards;
}

//shuffles deck by swapping every card with a random card
void Deck::shuffle()
{
    for(int i = 0; i < 52; i++)
    {
        int rng = rand() % 52;
        std::swap(cards[i], cards[rng]);
    }
    //std::cout << "Shuffled deck\n\n"; 
}

//prints cards
void Deck::printCards()
{
    for(int i = 0; i < 52; i++)
    {
        std::cout << cards[i] << ' ';
    };
    std::cout << std::endl;
}

//draws a card from the deck by returning the first card and cycling the deck
int Deck::drawCard()
{
    int card = cards[0];
    for(int i = 0; i < 51; i++)
    {
        cards[i] = cards[i + 1];
    }
    cards[51] = card;
    if(card > 10)
    {
        card = 10;
    }
    return card;
}

//gets sum of vector
int getTotal(std::vector<int> cards)
{
    int total = 0;
    for(int card : cards)
    {
        total += card;
    }
    return total;
}

//user inputs value of ace
int pAceLogic()
{
    std::string ace = "";
    while (ace != "1" && ace != "11")
    {
        std::cout << "Enter 1 or 11 for ace: ";
        std::cin >> ace;
    } 

    return (ace == "1") ? 1 : 11;
}

//returns 11 if the dealer doesn't bust as a result
int dAceLogic(int dTotal)
{
    if (dTotal > 21)
    {
        return 11;
    }
    else
    {
        return 1;
    }
}
