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

#endif

