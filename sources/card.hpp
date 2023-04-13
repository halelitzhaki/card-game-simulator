#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
using namespace std;

namespace ariel {
    class Card {
        private:
            string name;
            int number;
        public:
            Card();
            Card(int, string);
            Card(Card const &) = default;
            Card(Card &&) = default;
            Card& operator=(Card const &) = default;
            Card& operator=(Card &&) = default;
            ~Card();
            
            int getNumber();
            string getName();
    };
}

#endif