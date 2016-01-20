#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main(int argc, char *argv[])
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Paddles");
    sf::Event event;

    // just making sure I do something every day
    sf::Texture bgImage;
    if (!bgImage.loadFromFile("assets/images/paddlesBg.png"))
    {
        std::cerr << "[Error]: Unable to load background image" << std::endl;
        exit(-1);
    }
    sf::Sprite background;
    background.setTexture(bgImage);

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
        window.display();
    }
}
