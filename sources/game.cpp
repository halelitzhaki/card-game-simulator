#include "game.hpp"

using namespace ariel;

Game::Game(Player &p1, Player &p2) {
    player1 = &p1;
    player2 = &p2;

    string names[4] = {"Spades", "Hearts", "Diamonds", "Clubs"};

    // Initializing the deck
    for (int i = 0; i < 4; i++) {
        for(int j = 1; j <= 13; j++) {
            if(j == 1) {
                string name = "Ace of ";
                name.append(names[i]);
                Card card(1, name);
                cards.push_back(card);
            } 
            else if(j == 11) {
                string name = "Jack of ";
                name.append(names[i]);
                Card card(11, name);
                cards.push_back(card);
            }
            else if(j == 12) {
                string name = "Queen of ";
                name.append(names[i]);
                Card card(12, name);
                cards.push_back(card);
            }
            else if(j == 13) {
                string name = "King of ";
                name.append(names[i]);
                Card card(13, name);
                cards.push_back(card);
            }
            else {
                string name = to_string(j);
                name.append(" of ");
                name.append(names[i]);
                Card card(j, name);
                cards.push_back(card);
            }
        }
    }

    // Mixing the cards
    random_device rd;
    mt19937 gen(rd());
    shuffle(cards.begin(), cards.end(), gen);

    // Splitting the cards between two players
    int i = 0;
    for(Card c : cards) {
        if(i < 26) player1->getCardFromDeck(c);
        else player2->getCardFromDeck(c);
        i++;
    }
}

Game::Game() { }

Game::~Game() { }

void Game::playTurn() {
    if(player1 == player2) throw runtime_error("One player");
    if(player1->stacksize() == 0 || player2->stacksize() == 0) throw overflow_error("no more cards");
    playRounds++;
    Card p1Card = player1->getCard(), p2Card = player2->getCard();
    addLog(p1Card, p2Card);
    if(p1Card.getNumber() > p2Card.getNumber()) { // Player 1 wins
        player1->won(p1Card);
        player1->won(p2Card);
        p1Wins++;
    }
    else if(p1Card.getNumber() < p2Card.getNumber()) { // Player 2 wins
        player2->won(p1Card);
        player2->won(p2Card);
        p2Wins++;
    }
    else { // Draw
        vector<Card> drawCards;
        drawCards.push_back(p1Card);
        drawCards.push_back(p2Card);
        while(1) {
            if(player1->stacksize() == 0 || player1->stacksize() == 1 
            || player2->stacksize() == 0 || player2->stacksize() == 1) {
                return;
            }
            draws++;
            Card p1Down = player1->getCard(), p1Up = player1->getCard(),
                    p2Down = player2->getCard(), p2Up = player2->getCard();

            addLog(p1Up, p2Up);

            drawCards.push_back(p1Down);
            drawCards.push_back(p1Up);
            drawCards.push_back(p2Down);
            drawCards.push_back(p2Up);

            if(p1Up.getNumber() > p2Up.getNumber()) { // Player 1 wins
                for(Card c : drawCards) player1->won(c);
                p1Wins++;
                break;
            }
            else if(p1Up.getNumber() < p2Up.getNumber()) { // Player 2 wins
                for(Card c : drawCards) player2->won(c);
                p2Wins++;
                break;
            }
        }
    }
}

void Game::addLog(Card cardA, Card cardB) {
    if(cardA.getNumber() > cardB.getNumber()) {
        string turn = player1->getPlayerName();
        turn.append(" played ");
        turn.append(cardA.getName());
        turn.append(" ");
        turn.append(player2->getPlayerName());
        turn.append(" played ");
        turn.append(cardB.getName());
        turn.append(". ");
        turn.append(player1->getPlayerName());
        turn.append(" wins.\n");
        turns.push_back(turn);
    }
    else if (cardA.getNumber() < cardB.getNumber()) {
        string turn = player1->getPlayerName();
        turn.append(" played ");
        turn.append(cardA.getName());
        turn.append(" ");
        turn.append(player2->getPlayerName());
        turn.append(" played ");
        turn.append(cardB.getName());
        turn.append(". ");
        turn.append(player2->getPlayerName());
        turn.append(" wins.\n");
        turns.push_back(turn);    
    }
    else {
        string turn = player1->getPlayerName();
        turn.append(" played ");
        turn.append(cardA.getName());
        turn.append(" ");
        turn.append(player2->getPlayerName());
        turn.append(" played ");
        turn.append(cardB.getName());
        turn.append(". Draw.\n");
        turns.push_back(turn); 
    }
}

void Game::printLastTurn() {
    if(turns.empty()) return;
    cout << turns.back();
}

void Game::playAll() {
    while(player1->stacksize() >= 1 && player2->stacksize() >= 1) {
        playTurn();
    }
}

void Game::printWiner() {
    cout << "The winner is : ";
    if(player1->cardesTaken() > player2->cardesTaken()) cout << player1->getPlayerName() << endl;
    else cout << player2->getPlayerName() << endl;
}

void Game::printLog() {
    for(string t : turns) {
        cout << t;
    }
}

void Game::printStats() {
    cout << "Game Statistics:\n"; 
    printWiner(); 
    cout << "There was " << playRounds << " play rounds.\n" << player1->getPlayerName() << " statistics are:\nWinning - " << p1Wins 
    << " times, with " << player1->cardesTaken() << " cards.\n\n"
    << player2->getPlayerName() << " statistics are:\nWinning - " << p2Wins
    << " times, with " << player2->cardesTaken() << " cards.\n\n";
}

int Game::getPlayRounds() {
    return playRounds;
}

Player* Game::getPlayer1() {
    return player1;
}

Player* Game::getPlayer2() {
    return player2;
}