#ifndef GAME_HPP
#define GAME_HPP

#include "card.hpp"
#include "player.hpp"
#include <vector>
#include <random>
#include <exception>
#include <string.h>

namespace ariel {
    class Game
    {
        private:
            Player *player1, *player2;
            vector<string> turns;
            vector<Card> cards;
            int playRounds = 0, p1Wins = 0, p2Wins = 0, draws = 0;

        public:
            Game(Player&,Player&);
            Game();
            Game(Game const &) = default;
            Game(Game &&) = default;
            Game& operator=(Game const &) = delete;
            Game& operator=(Game &&) = delete;
            ~Game();

            void playTurn();
            void addLog(Card, Card);
            void printLastTurn();
            void playAll();
            void printWiner();
            void printLog(); 
            void printStats();
            int getPlayRounds();
            Player* getPlayer1();
            Player* getPlayer2();
    };
}

#endif