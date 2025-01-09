#include "Move.h"

// Move implementations
Move::Move(const std::string& name, int power, int accuracy)
    : name(name), power(power), accuracy(accuracy) {}

std::string Move::getName() const {
    return name;
}

int Move::getPower() const {
    return power;
}

int Move::getAccuracy() const {
    return accuracy;
}

int Move::calculateDamage() const {
    return power * (accuracy / 100.0);
}

std::shared_ptr<Move> Move::clone() const {
    return std::make_shared<Move>(*this);
}

std::ostream& operator<<(std::ostream& os, const Move& move) {
    os << move.name << " (Power: " << move.power << ", Accuracy: " << move.accuracy << ")";
    return os;
}

// FireMove implementations
FireMove::FireMove(const std::string& name, int power, int accuracy)
    : Move(name, power, accuracy), damageCalc(1.5f) {}

int FireMove::calculateDamage() const {
    return damageCalc.calculate(Move::calculateDamage());
}

std::shared_ptr<Move> FireMove::clone() const {
    return std::make_shared<FireMove>(*this);
}

// WaterMove implementations
WaterMove::WaterMove(const std::string& name, int power, int accuracy)
    : Move(name, power, accuracy), damageCalc(1.3f) {}

int WaterMove::calculateDamage() const {
    return damageCalc.calculate(Move::calculateDamage());
}

std::shared_ptr<Move> WaterMove::clone() const {
    return std::make_shared<WaterMove>(*this);
}