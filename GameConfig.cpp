#include "GameConfig.h"
#include "Pokemon.h"

GameConfig* GameConfig::instance = nullptr;

GameConfig::GameConfig() {
    // Initialize type advantages
    typeAdvantages["FireWater"] = 0.5f;
    typeAdvantages["FireGrass"] = 2.0f;
    typeAdvantages["WaterFire"] = 2.0f;
    typeAdvantages["WaterGround"] = 2.0f;
    typeAdvantages["ElectricWater"] = 2.0f;
    typeAdvantages["ElectricGround"] = 0.0f;
    typeAdvantages["GrassWater"] = 2.0f;
    typeAdvantages["GrassFire"] = 0.5f;
    typeAdvantages["GrassGround"] = 2.0f;
    typeAdvantages["WaterRock"] = 2.0f;
    typeAdvantages["ElectricFlying"] = 2.0f;
}

GameConfig::~GameConfig() {
    delete instance;
    instance = nullptr;
}

GameConfig& GameConfig::getInstance() {
    if (instance == nullptr) {
        instance = new GameConfig();
    }
    return *instance;
}

float GameConfig::getTypeAdvantage(const std::string& attackerType, const std::string& defenderType) {
    std::string key = attackerType + defenderType;
    auto it = typeAdvantages.find(key);
    return it != typeAdvantages.end() ? it->second : 1.0f;
}

std::shared_ptr<Pokemon> PokemonFactory::createPokemon(const std::string& type,
                                                      const std::string& name,
                                                      int hp, int attack, int defense) {
    if (type == "Fire") {
        return std::make_shared<FirePokemon>(name, hp, attack, defense);
    } else if (type == "Water") {
        return std::make_shared<WaterPokemon>(name, hp, attack, defense);
    } else if (type == "Electric") {
        return std::make_shared<ElectricPokemon>(name, hp, attack, defense);
    } else if (type == "Grass") {
        return std::make_shared<GrassPokemon>(name, hp, attack, defense);
    }
    throw PokemonException("Unknown Pokemon type: " + type);
}