#include "AppleCatcher.h"
#include <cstdlib>
#include <ctime>
using namespace std;
AppleCatcher::AppleCatcher(int screenWidth, int screenHeight)
    : window(sf::VideoMode(screenWidth, screenHeight), "Apple Catcher"),
    score(0), highScore(0), appleSpeed(200.0f), basketSpeed(300.0f), isGameOver(false) {

    if (!appleTexture.loadFromFile("apple.png")) {
        std::cerr << "Failed to load apple texture!" << std::endl;
    }
    if (!basketTexture.loadFromFile("basket.png")) {
        std::cerr << "Failed to load basket texture!" << std::endl;
    }
    if (!backgroundTexture.loadFromFile("background.jpg")) {
        std::cerr << "Failed to load background texture!" << std::endl;
    }
    if (!gameOverTexture.loadFromFile("gameover.png")) {
        std::cerr << "Failed to load game over texture!" << std::endl;
    }
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    appleSprite.setTexture(appleTexture);
    appleSprite.setScale(0.1f, 0.1f); // Adjust the scale to make the apple smaller

    basketSprite.setTexture(basketTexture);
    basketSprite.setScale(0.5f, 0.5f);
    basketSprite.setPosition(screenWidth / 2 - basketSprite.getLocalBounds().width / 2,
        screenHeight - basketSprite.getLocalBounds().height);

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(float(screenWidth) / backgroundTexture.getSize().x, float(screenHeight) / backgroundTexture.getSize().y);

    gameOverSprite.setTexture(gameOverTexture);
    gameOverSprite.setPosition(screenWidth / 2 - gameOverSprite.getLocalBounds().width / 2,
        screenHeight / 2 - gameOverSprite.getLocalBounds().height / 2);

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    highScoreText.setFont(font);
    highScoreText.setCharacterSize(24);
    highScoreText.setFillColor(sf::Color::White);
    highScoreText.setPosition(screenWidth - 150, 10);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(24);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setString("Press C to continue");
    gameOverText.setPosition(screenWidth / 2 - gameOverText.getLocalBounds().width / 2,
        screenHeight / 2 + gameOverSprite.getLocalBounds().height / 2 + 20);

    resetApple();
}

void AppleCatcher::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        handleInput(deltaTime);
        if (!isGameOver) {
            update(deltaTime);
        }
        render();
    }
}

void AppleCatcher::handleInput(float deltaTime) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }

    if (!isGameOver) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (basketSprite.getPosition().x > 0) {
                basketSprite.move(-basketSpeed * deltaTime, 0);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (basketSprite.getPosition().x + basketSprite.getGlobalBounds().width < window.getSize().x) {
                basketSprite.move(basketSpeed * deltaTime, 0);
            }
        }
    }
    else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            resetGame();
        }
    }
}

void AppleCatcher::update(float deltaTime) {
    // Update the position of the apple
    appleSprite.move(0, appleSpeed * deltaTime);

    // Check for collision with the basket
    if (appleSprite.getGlobalBounds().intersects(basketSprite.getGlobalBounds())) {
        score++;
        resetApple();
    }

    // Check if apple is out of bounds
    if (appleSprite.getPosition().y > window.getSize().y) {
        gameOver();
    }

    updateHighScore();

    scoreText.setString("Score: " + std::to_string(score));
}

void AppleCatcher::render() {
    window.clear();
    window.draw(backgroundSprite);
    if (!isGameOver) {
        window.draw(appleSprite);
        window.draw(basketSprite);
        window.draw(scoreText);
    }
    else {
        window.draw(gameOverSprite);
        window.draw(gameOverText);
    }
    window.draw(highScoreText);
    window.display();
}

void AppleCatcher::resetApple() {
    float xPos = static_cast<float>(std::rand() % (window.getSize().x - static_cast<int>(appleSprite.getGlobalBounds().width)));
    appleSprite.setPosition(xPos, 0); // Set the apple position at the top of the screen
}

void AppleCatcher::resetGame() {
    score = 0;
    isGameOver = false;
    resetApple();
}

void AppleCatcher::gameOver() {
    isGameOver = true;
}

void AppleCatcher::updateHighScore() {
    if (score > highScore) {
        highScore = score;
        highScoreText.setString("High Score: " + std::to_string(highScore));
    }
}
