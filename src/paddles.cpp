#include "paddles.hpp"

/* constructor for the Paddles object */
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
    loadTexture(enemySprite, paddleTexture, "assets/images/player.png");
    playerSprite.setPosition(50, 190);
    enemySprite.setPosition(590, 190);
}

/* runs the main game loop */
void Paddles::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

/* handles any input from the window */
void Paddles::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
        }
    }
}

/* updates game logic */
void Paddles::update()
{
}

/* draws the images to the screen */
void Paddles::render()
{
    window.clear();
    window.draw(bgSprite);
    window.draw(playerSprite);
    window.draw(enemySprite);
    window.display();
}

