#ifndef POKEMON_EXCEPTIONS_H
#define POKEMON_EXCEPTIONS_H

#include <string>
#include <exception>

class PokemonException : public std::exception {
protected:
    std::string message;
public:
    explicit PokemonException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class MoveLimitException : public PokemonException {
public:
    MoveLimitException() : PokemonException("Pokemon cannot learn more than 4 moves!") {}
};

class InvalidMoveException : public PokemonException {
public:
    InvalidMoveException() : PokemonException("Invalid move selected!") {}
};

#endif //POKEMON_EXCEPTIONS_H