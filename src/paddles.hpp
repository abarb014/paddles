#ifndef PADDLES_HPP
#define PADDLES_HPP

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <SFML/Graphics.hpp>

class Paddles
{
    public:
        Paddles(); // constructor
        void run();

    private:
        /* main game window */
        sf::RenderWindow window;
        static const sf::Time TimePerFrame;
        static const float xRange;
        static const float yRange;
        sf::Font font;
        sf::Text playerScore;
        sf::Text enemyScore;
        unsigned int scored;
        void ballScored(const unsigned int &player);

        /* background */
        sf::Texture bgTexture;
        sf::Sprite bgSprite;

        /* paddle */
        sf::Texture paddleTexture;
        sf::Sprite playerSprite;
        sf::Sprite enemySprite;
        static const float playerSpeed;
        static const float enemySpeed;
        bool playerUp;
        bool playerDown;

        /* ball */
        sf::Texture ballTexture;
        sf::Sprite ballSprite;
        sf::Vector2f ballDirection;
        static const float ballSpeed;
        void moveBall(sf::Time deltaTime);
        void checkCollisions();
        void bounceBall(const sf::Sprite &sprite);
        static const float ballMaxAngle;

        /* ai */
        void enemyAI(sf::Time deltaTime);

        // main game functions
        void processEvents();
        void update(sf::Time deltaTime);
        void render();

        // helper functions
        void loadTexture(sf::Sprite &sprite, sf::Texture &texture, const std::string &filename);
        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
        float toRadians(float angle);
        void initScoreboard();
        float serveAngle(void);
        float pickSide(void);
};

#endif

