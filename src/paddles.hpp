#ifndef PADDLES_HPP
#define PADDLES_HPP

#include <iostream>
#include <cstdlib>
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

        /* entity data */
        bool playerUp;
        bool playerDown;

        // main game functions
        void processEvents();
        void update();
        void render();

        // helper functions
        void loadTexture(sf::Sprite &sprite, sf::Texture &texture, const std::string &filename);
        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
};

#endif

