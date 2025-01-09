#include "Pokemon.h"
#include "GameConfig.h"

// Static member initialization
int Pokemon::totalPokemon = 0;

// Pokemon implementations
Pokemon::Pokemon(const std::string& name, int hp, int attack, int defense)
    : name(name), hp(hp), maxHp(hp), attack(attack), defense(defense) {
    ++totalPokemon;
}

int Pokemon::getTotalPokemon() {
    return totalPokemon;
}

std::string Pokemon::getName() const { return name; }
int Pokemon::getHp() const { return hp; }
int Pokemon::getMaxHp() const { return maxHp; }
int Pokemon::getAttack() const { return attack; }
std::string Pokemon::getType() const { return type; }
const std::vector<std::shared_ptr<Move>>& Pokemon::getMoves() const { return moves; }

void Pokemon::addMove(const Move& move) {
    if (moves.size() >= 4) {
        throw MoveLimitException();
    }
    moves.push_back(move.clone());
}

bool Pokemon::isDefeated() const {
    return hp <= 0;
}

void Pokemon::useMove(Pokemon& target, size_t moveIndex) {
    if (moveIndex >= moves.size()) {
        throw InvalidMoveException();
    }

    float typeAdvantageMultiplier = getTypeAdvantage(target);
    int baseDamage = moves[moveIndex]->calculateDamage() * (attack / 100.0);
    int finalDamage = static_cast<int>(baseDamage * typeAdvantageMultiplier);
    finalDamage = std::max(1, finalDamage - target.defense / 4);

    target.hp = std::max(0, target.hp - finalDamage);

    std::cout << name << " used " << moves[moveIndex]->getName() << "!\n";
    if (typeAdvantageMultiplier > 1.0f) {
        std::cout << "It's super effective!\n";
    } else if (typeAdvantageMultiplier < 1.0f) {
        std::cout << "It's not very effective...\n";
    }
    std::cout << "Dealt " << finalDamage << " damage to " << target.getName() << "!\n";
}

std::ostream& operator<<(std::ostream& os, const Pokemon& pokemon) {
    os << pokemon.name << " (HP: " << pokemon.hp << "/" << pokemon.maxHp << ")\n";
    os << "Moves:\n";
    for (size_t i = 0; i < pokemon.moves.size(); ++i) {
        os << i + 1 << ". " << *pokemon.moves[i] << "\n";
    }
    return os;
}

// FirePokemon implementations
FirePokemon::FirePokemon(const std::string& name, int hp, int attack, int defense)
    : Pokemon(name, hp, attack, defense) {
    type = "Fire";
}

float FirePokemon::getTypeAdvantage(const Pokemon& target) const {
    return GameConfig::getInstance().getTypeAdvantage(type, target.getType());
}

std::shared_ptr<Pokemon> FirePokemon::clone() const {
    return std::make_shared<FirePokemon>(*this);
}

// WaterPokemon implementations
WaterPokemon::WaterPokemon(const std::string& name, int hp, int attack, int defense)
    : Pokemon(name, hp, attack, defense) {
    type = "Water";
}

float WaterPokemon::getTypeAdvantage(const Pokemon& target) const {
    return GameConfig::getInstance().getTypeAdvantage(type, target.getType());
}

std::shared_ptr<Pokemon> WaterPokemon::clone() const {
    return std::make_shared<WaterPokemon>(*this);
}

// ElectricPokemon implementations
ElectricPokemon::ElectricPokemon(const std::string& name, int hp, int attack, int defense)
    : Pokemon(name, hp, attack, defense) {
    type = "Electric";
}

float ElectricPokemon::getTypeAdvantage(const Pokemon& target) const {
    return GameConfig::getInstance().getTypeAdvantage(type, target.getType());
}

std::shared_ptr<Pokemon> ElectricPokemon::clone() const {
    return std::make_shared<ElectricPokemon>(*this);
}

// GrassPokemon implementations
GrassPokemon::GrassPokemon(const std::string& name, int hp, int attack, int defense)
    : Pokemon(name, hp, attack, defense) {
    type = "Grass";
}

float GrassPokemon::getTypeAdvantage(const Pokemon& target) const {
    return GameConfig::getInstance().getTypeAdvantage(type, target.getType());
}

std::shared_ptr<Pokemon> GrassPokemon::clone() const {
    return std::make_shared<GrassPokemon>(*this);
}