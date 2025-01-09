#ifndef POKEMON_H
#define POKEMON_H

#include "Move.h"
#include "exceptions.h"
#include <vector>
#include <memory>
#include <string>

class Pokemon {
protected:
    std::string name;
    int hp;
    int maxHp;
    int attack;
    int defense;
    std::string type;
    std::vector<std::shared_ptr<Move>> moves;

    static int totalPokemon;

public:
    Pokemon(const std::string& name = "", int hp = 100, int attack = 50, int defense = 50);
    virtual ~Pokemon() = default;

    static int getTotalPokemon();

    std::string getName() const;
    int getHp() const;
    int getMaxHp() const;
    int getAttack() const;
    std::string getType() const;
    const std::vector<std::shared_ptr<Move>>& getMoves() const;

    virtual void addMove(const Move& move);
    bool isDefeated() const;
    virtual void useMove(Pokemon& target, size_t moveIndex);

    virtual float getTypeAdvantage(const Pokemon& target) const = 0;
    virtual std::shared_ptr<Pokemon> clone() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Pokemon& pokemon);
};

class FirePokemon : public Pokemon {
public:
    FirePokemon(const std::string& name, int hp, int attack, int defense);
    float getTypeAdvantage(const Pokemon& target) const override;
    std::shared_ptr<Pokemon> clone() const override;
};

class WaterPokemon : public Pokemon {
public:
    WaterPokemon(const std::string& name, int hp, int attack, int defense);
    float getTypeAdvantage(const Pokemon& target) const override;
    std::shared_ptr<Pokemon> clone() const override;
};

class ElectricPokemon : public Pokemon {
public:
    ElectricPokemon(const std::string& name, int hp, int attack, int defense);
    float getTypeAdvantage(const Pokemon& target) const override;
    std::shared_ptr<Pokemon> clone() const override;
};

class GrassPokemon : public Pokemon {
public:
    GrassPokemon(const std::string& name, int hp, int attack, int defense);
    float getTypeAdvantage(const Pokemon& target) const override;
    std::shared_ptr<Pokemon> clone() const override;
};

#endif //POKEMON_H