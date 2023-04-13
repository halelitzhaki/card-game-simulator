#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "card.hpp"
#include <vector>
using namespace std;

namespace ariel {
    class Player
    {
        private:
            string *name;
            vector<Card> cardsTaken,cards;

        public:
            Player();
            Player(string);
            Player(Player const &) = delete;
            Player(Player &&) = delete;
            Player& operator=(Player const &) = delete;
            Player& operator=(Player &&) = delete;
            ~Player();

            Card getCard();
            int stacksize();
            int cardesTaken();
            void won(Card);

            vector<Card> getCardsTaken();
            vector<Card> getCards();
            Card getLastCardTaken();
            string getPlayerName();

            void getCardFromDeck(Card);
    };
}

#endif