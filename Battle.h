#ifndef POKEMON_BATTLE_H
#define POKEMON_BATTLE_H

#include "Pokemon.h"
#include <memory>
#include <string>

class BattleObserver {
public:
    virtual ~BattleObserver() = default;
    virtual void onMoveUsed(const std::string& attacker, const std::string& move, int damage) = 0;
    virtual void onPokemonDefeated(const std::string& pokemon) = 0;
};

class BattleLogger : public BattleObserver {
public:
    void onMoveUsed(const std::string& attacker, const std::string& move, int damage) override;
    void onPokemonDefeated(const std::string& pokemon) override;
};

class Battle {
private:
    std::shared_ptr<Pokemon> player1;
    std::shared_ptr<Pokemon> player2;
    std::string player1Name;
    std::string player2Name;
    bool isPlayer1Turn;
    std::shared_ptr<BattleLogger> battleLogger;

public:
    Battle(std::shared_ptr<Pokemon> p1, std::shared_ptr<Pokemon> p2,
           const std::string& p1Name, const std::string& p2Name);

    void executeTurn(size_t moveIndex);
    bool isGameOver() const;
    std::string getWinner() const;
    bool isFirstPlayerTurn() const;
    std::string getCurrentPlayerName() const;

    friend std::ostream& operator<<(std::ostream& os, const Battle& battle);
};

#endif //POKEMON_BATTLE_H