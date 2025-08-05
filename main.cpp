#include "AppleCatcher.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    AppleCatcher game(SCREEN_WIDTH, SCREEN_HEIGHT);
    game.run();

    return 0;
}
