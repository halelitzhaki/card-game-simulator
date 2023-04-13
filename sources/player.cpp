#include "player.hpp"

using namespace ariel;

Player::Player() { }

Player::Player(string _name) {
    name = &_name;
}

Player::~Player() { }

Card Player::getCard() {
    Card c = cards.at(cards.size() - 1);
    cards.pop_back();
    return c;
}

int Player::stacksize() {
    return cards.size();
}

int Player::cardesTaken() {
    return cardsTaken.size();
}

void Player::won(Card card) {
    cardsTaken.push_back(card);
}

void Player::getCardFromDeck(Card card) {
    cards.push_back(card);
}

vector<Card> Player::getCardsTaken() {
    return cardsTaken;
}

vector<Card> Player::getCards() {
    return cards;
}

Card Player::getLastCardTaken() {
    return cardsTaken.back();
}

string Player::getPlayerName() {
    return *name;
}