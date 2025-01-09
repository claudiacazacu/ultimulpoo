#include "Battle.h"

void BattleLogger::onMoveUsed(const std::string& attacker, const std::string& move, int damage) {
    std::cout << attacker << " used " << move << " dealing " << damage << " damage!\n";
}

void BattleLogger::onPokemonDefeated(const std::string& pokemon) {
    std::cout << pokemon << " has been defeated!\n";
}

Battle::Battle(std::shared_ptr<Pokemon> p1, std::shared_ptr<Pokemon> p2,
               const std::string& p1Name, const std::string& p2Name)
    : player1(p1), player2(p2),
      player1Name(p1Name), player2Name(p2Name),
      isPlayer1Turn(true),
      battleLogger(std::make_shared<BattleLogger>()) {}

void Battle::executeTurn(size_t moveIndex) {
    if (isGameOver()) {
        throw PokemonException("Battle is already over!");
    }

    Pokemon& attacker = isPlayer1Turn ? *player1 : *player2;
    Pokemon& defender = isPlayer1Turn ? *player2 : *player1;

    int initialHp = defender.getHp();
    try {
        attacker.useMove(defender, moveIndex);
        int damage = initialHp - defender.getHp();
        battleLogger->onMoveUsed(attacker.getName(),
                               attacker.getMoves()[moveIndex]->getName(),
                               damage);

        if (defender.isDefeated()) {
            battleLogger->onPokemonDefeated(defender.getName());
        }
    } catch (const InvalidMoveException& e) {
        throw;
    }

    isPlayer1Turn = !isPlayer1Turn;
}

bool Battle::isGameOver() const {
    return player1->isDefeated() || player2->isDefeated();
}

std::string Battle::getWinner() const {
    if (!isGameOver()) return "Battle is still ongoing";
    if (player1->isDefeated()) return player2Name;
    return player1Name;
}

bool Battle::isFirstPlayerTurn() const {
    return isPlayer1Turn;
}

std::string Battle::getCurrentPlayerName() const {
    return isPlayer1Turn ? player1Name : player2Name;
}

std::ostream& operator<<(std::ostream& os, const Battle& battle) {
    os << "\nCurrent turn: " << battle.getCurrentPlayerName() << "\n\n";
    os << battle.player1Name << "'s Pokemon:\n" << *battle.player1 << "\n";
    os << battle.player2Name << "'s Pokemon:\n" << *battle.player2;
    return os;
}