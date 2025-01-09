#ifndef POKEMON_GAMECONFIG_H
#define POKEMON_GAMECONFIG_H

#include <string>
#include <map>
#include <memory>
#include "Pokemon.h"

class GameConfig {
private:
    static GameConfig* instance;
    std::map<std::string, float> typeAdvantages;

    GameConfig();

public:
    virtual ~GameConfig();
    static GameConfig& getInstance();
    float getTypeAdvantage(const std::string& attackerType, const std::string& defenderType);
    static void cleanup() {
        delete instance;
        instance = nullptr;
    }
};

class PokemonFactory {
public:
    static std::shared_ptr<Pokemon> createPokemon(const std::string& type,
                                                const std::string& name,
                                                int hp, int attack, int defense);
};

#endif //POKEMON_GAMECONFIG_H