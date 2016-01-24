#ifndef PADDLES_HPP
#define PADDLES_HPP

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <SFML/Graphics.hpp>

class Paddles
{
    public:
        Paddles(); // constructor
        void run();

    private:
        /* main game window */
        sf::RenderWindow window;

        /* graphical variables */
        sf::Texture bgTexture;
        sf::Sprite bgSprite;

        sf::Texture paddleTexture;
        sf::Sprite playerSprite;
        sf::Sprite enemySprite;

        sf::Texture ballTexture;
        sf::Sprite ballSprite;

        /* entity data */
        static const float playerSpeed;
        bool playerUp;
        bool playerDown;

        sf::Vector2f ballDirection;
        float ballAngle;
        static const float ballSpeed;

        static const sf::Time TimePerFrame;

        // main game functions
        void processEvents();
        void update(sf::Time deltaTime);
        void render();

        // helper functions
        void loadTexture(sf::Sprite &sprite, sf::Texture &texture, const std::string &filename);
        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
        float toRadians(float angle);
};

#endif

