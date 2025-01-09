#include "GameManager.h"
#include <iostream>
#include <limits>

GameManager::GameManager() {
    initializePokemon();
}

void GameManager::initializePokemon() {
    availablePokemon = {
        PokemonFactory::createPokemon("Electric", "Pikachu", 90, 55, 40),
        PokemonFactory::createPokemon("Fire", "Charmander", 85, 60, 45),
        PokemonFactory::createPokemon("Water", "Squirtle", 88, 48, 65),
        PokemonFactory::createPokemon("Grass", "Bulbasaur", 95, 49, 49)
    };

    availablePokemon[0]->addMove(Move("Thunder Shock", 40, 100));
    availablePokemon[0]->addMove(Move("Quick Attack", 40, 100));
    availablePokemon[0]->addMove(Move("Thunder Wave", 0, 90));
    availablePokemon[0]->addMove(Move("Thunder", 110, 70));

    availablePokemon[1]->addMove(FireMove("Ember", 40, 100));
    availablePokemon[1]->addMove(Move("Scratch", 40, 100));
    availablePokemon[1]->addMove(FireMove("Dragon Breath", 60, 100));
    availablePokemon[1]->addMove(FireMove("Fire Spin", 35, 85));

    availablePokemon[2]->addMove(WaterMove("Water Gun", 40, 100));
    availablePokemon[2]->addMove(Move("Tackle", 40, 100));
    availablePokemon[2]->addMove(WaterMove("Bubble", 40, 100));
    availablePokemon[2]->addMove(WaterMove("Water Pulse", 60, 100));

    availablePokemon[3]->addMove(Move("Vine Whip", 45, 100));
    availablePokemon[3]->addMove(Move("Tackle", 40, 100));
    availablePokemon[3]->addMove(Move("Leech Seed", 0, 90));
    availablePokemon[3]->addMove(Move("Razor Leaf", 55, 95));
}

std::string GameManager::getPlayerName(int playerNumber) {
    std::string name;
    std::cout << "Player " << playerNumber << ", enter your name: ";
    std::getline(std::cin, name);
    return name;
}

void GameManager::displayAvailablePokemon() {
    std::cout << "\nAvailable Pokemon:\n";
    for (size_t i = 0; i < availablePokemon.size(); ++i) {
        std::cout << i + 1 << ". " << availablePokemon[i]->getName()
                 << " (" << availablePokemon[i]->getType() << ")\n";
    }
}

size_t GameManager::getPokemonChoice(const std::string& playerName) {
    while (true) {
        std::cout << playerName << ", choose your Pokemon (1-"
                 << availablePokemon.size() << "): ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice >= 1 && choice <= static_cast<int>(availablePokemon.size())) {
            return static_cast<size_t>(choice - 1);
        }
        std::cout << "Invalid choice. Please try again.\n";
    }
}

void GameManager::startGame() {
    std::cout << "Welcome to Pokemon Battle!\n\n";
    std::cout << "Total Pokemon available: " << Pokemon::getTotalPokemon() << "\n\n";

    try {
        std::string player1Name = getPlayerName(1);
        std::string player2Name = getPlayerName(2);

        displayAvailablePokemon();

        size_t p1Choice = getPokemonChoice(player1Name);
        size_t p2Choice = getPokemonChoice(player2Name);

        auto p1Pokemon = availablePokemon[p1Choice]->clone();
        auto p2Pokemon = availablePokemon[p2Choice]->clone();

        Battle battle(p1Pokemon, p2Pokemon, player1Name, player2Name);

        while (!battle.isGameOver()) {
            std::cout << battle << "\n";

            std::cout << battle.getCurrentPlayerName()
                     << ", choose your move (1-4): ";
            int moveChoice;
            std::cin >> moveChoice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (moveChoice < 1 || moveChoice > 4) {
                std::cout << "Invalid move choice. Please choose 1-4.\n";
                continue;
            }

            try {
                battle.executeTurn(moveChoice - 1);

                // Display post-turn stats
                std::cout << "\n=== Current Status ===\n";
                std::cout << player1Name << "'s " << p1Pokemon->getName()
                         << " HP: " << p1Pokemon->getHp() << "/"
                         << p1Pokemon->getMaxHp() << "\n";
                std::cout << player2Name << "'s " << p2Pokemon->getName()
                         << " HP: " << p2Pokemon->getHp() << "/"
                         << p2Pokemon->getMaxHp() << "\n";
                std::cout << "==================\n\n";

            } catch (const PokemonException& e) {
                std::cout << "Error: " << e.what() << "\n";
                continue;
            }
        }

        std::cout << "\nBattle Over! " << battle.getWinner() << " wins!\n";

    } catch (const PokemonException& e) {
        std::cout << "Game error: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << "\n";
    }
}