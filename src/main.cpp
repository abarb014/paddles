#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main(int argc, char *argv[])
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Paddles");
    sf::Event event;

    // load and setup background
    sf::Texture bgImage;
    if (!bgImage.loadFromFile("assets/images/paddlesBg.png"))
    {
        std::cerr << "[Error]: Unable to load background image" << std::endl;
        exit(-1);
    }
    sf::Sprite background;
    background.setTexture(bgImage);

    // load and setup player paddle
    sf::Texture playerImage;
    if (!playerImage.loadFromFile("assets/images/player.png"))
    {
        std::cerr << "[Error]: Unable to load player image" << std::endl;
        exit(-1);
    }
    sf::Sprite playerPaddle;
    playerPaddle.setTexture(playerImage);
    playerPaddle.setPosition(100, 240);

    // main game loop
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(background);
        window.draw(playerPaddle);
        window.display();
    }
}
