#ifndef PADDLES_H
#define PADDLES_H

#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

class Paddles
{
    public:
        Paddles(); // constructor
        void run();

    private:
        sf::RenderWindow window;

        sf::Texture bgTexture;
        sf::Sprite bgSprite;

        sf::Texture paddleTexture;
        sf::Sprite playerSprite;
        sf::Sprite enemySprite;

        // main game functions
        void processEvents();
        void update();
        void render();

        // helper functions
        void loadTexture(sf::Sprite &sprite, sf::Texture &texture, const std::string &filename)
        {
            if (!texture.loadFromFile(filename))
            {
                std::cerr << "[Error]: Unable to load texture file \"" << filename << "\"" << std::endl;
                exit(-1);
            }
            sprite.setTexture(texture);
        }
};

Paddles::Paddles()
: window(sf::VideoMode(640, 480), "Paddles")
, bgTexture()
, bgSprite()
, paddleTexture()
, playerSprite()
, enemySprite()
{
    loadTexture(bgSprite, bgTexture, "assets/images/paddlesBg.png");
    loadTexture(playerSprite, paddleTexture, "assets/images/player.png");
    loadTexture(enemySprite, paddleTexture, "addets/images/player.png");
    playerSprite.setPosition(50, 190);
    enemySprite.setPosition(590, 190);
}

void Paddles::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

#endif
