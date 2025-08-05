#ifndef APPLE_CATCHER_H
#define APPLE_CATCHER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class AppleCatcher {
public:
    AppleCatcher(int screenWidth, int screenHeight);

    void run();

private:
    void handleInput(float deltaTime);
    void update(float deltaTime);
    void render();
    void resetApple();
    void resetGame();
    void gameOver();
    void updateHighScore();

    sf::RenderWindow window;
    sf::Texture appleTexture;
    sf::Sprite appleSprite;
    sf::Texture basketTexture;
    sf::Sprite basketSprite;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture gameOverTexture;
    sf::Sprite gameOverSprite;
    sf::Font font;
    sf::Text scoreText;
    sf::Text highScoreText;
    sf::Text gameOverText;
    int score;
    int highScore;
    bool isGameOver;

    float appleSpeed;
    float basketSpeed;
};

#endif // APPLE_CATCHER_H
