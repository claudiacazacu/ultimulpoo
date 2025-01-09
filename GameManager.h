#ifndef POKEMON_GAMEMANAGER_H
#define POKEMON_GAMEMANAGER_H

#include "Pokemon.h"
#include "Battle.h"
#include "GameConfig.h"
#include "Move.h"
#include <vector>
#include <memory>

class GameManager {
private:
    std::vector<std::shared_ptr<Pokemon>> availablePokemon;

    void initializePokemon();
    std::string getPlayerName(int playerNumber);
    void displayAvailablePokemon();
    size_t getPokemonChoice(const std::string& playerName);

public:
    GameManager();
    void startGame();
};

#endif //POKEMON_GAMEMANAGER_H