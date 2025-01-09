#include "GameManager.h"
#include <iostream>

int main() {
    try {
        GameManager game;
        game.startGame();

        // Cleanup singleton
        GameConfig::cleanup();
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}