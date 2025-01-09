#ifndef POKEMON_MOVE_H
#define POKEMON_MOVE_H

#include <string>
#include <memory>
#include <iostream>

template<typename T>
class DamageCalculator {
private:
    T modifier;
public:
    explicit DamageCalculator(T mod) : modifier(mod) {}
    int calculate(int baseDamage) const {
        return static_cast<int>(baseDamage * static_cast<double>(modifier));
    }
};

class Move {
protected:
    std::string name;
    int power;
    int accuracy;

public:
    Move(const std::string& name = "", int power = 0, int accuracy = 0);
    virtual ~Move() = default;

    std::string getName() const;
    int getPower() const;
    int getAccuracy() const;

    virtual int calculateDamage() const;
    virtual std::shared_ptr<Move> clone() const;
    friend std::ostream& operator<<(std::ostream& os, const Move& move);
};

class FireMove : public Move {
private:
    DamageCalculator<float> damageCalc;
public:
    FireMove(const std::string& name, int power, int accuracy);
    int calculateDamage() const override;
    std::shared_ptr<Move> clone() const override;
};

class WaterMove : public Move {
private:
    DamageCalculator<float> damageCalc;
public:
    WaterMove(const std::string& name, int power, int accuracy);
    int calculateDamage() const override;
    std::shared_ptr<Move> clone() const override;
};

#endif //POKEMON_MOVE_H