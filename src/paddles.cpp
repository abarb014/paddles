#include "paddles.hpp"

/* constructor for the Paddles object */
Paddles::Paddles()
: window(sf::VideoMode(640, 480), "Paddles")
, bgTexture()
, bgSprite()
, paddleTexture()
, playerSprite()
, enemySprite()
, playerUp(false)
, playerDown(false)
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
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            default:
                break;
        }
    }
}

/* updates game logic */
void Paddles::update()
{
    /* handle player movement */
    sf::Vector2f playerMov (0.f, 0.f);
    if (playerUp)
        playerMov.y += 1.f;
    else if (playerDown)
        playerMov.y -= 1.f;

    playerSprite.move(playerMov);
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

void Paddles::loadTexture(sf::Sprite &sprite, sf::Texture &texture, const std::string &filename)
{
    if (!texture.loadFromFile(filename))
    {
        std::cerr << "[Error]: Unable to load texture file \"" << filename << "\"" << std::endl;
        exit(-1);
    }
    sprite.setTexture(texture);
}

/* move the player sprite based on keyboard input */
void Paddles::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::Up)
        playerUp = isPressed;
    else if (key == sf::Keyboard::Down)
        playerDown = isPressed;
}
