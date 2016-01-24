#include "paddles.hpp"

const float Paddles::playerSpeed = 300.f;
const float Paddles::ballSpeed = 350.f;
const sf::Time Paddles::TimePerFrame = sf::seconds(1.f/60.f);

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
, ballTexture()
, ballSprite()
, ballAngle(30)
, ballDirection()
{
    loadTexture(bgSprite, bgTexture, "assets/images/paddlesBg.png");
    loadTexture(playerSprite, paddleTexture, "assets/images/player.png");
    loadTexture(enemySprite, paddleTexture, "assets/images/player.png");
    loadTexture(ballSprite, ballTexture, "assets/images/ball.png");
    playerSprite.setPosition(50, 190);
    enemySprite.setPosition(583, 190);
    ballSprite.setPosition(160, 245);
    
    ballDirection.x = cos(toRadians(ballAngle)) * ballSpeed;
    ballDirection.y = -1.f * sin(toRadians(ballAngle)) * ballSpeed;
}

/* runs the main game loop */
void Paddles::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (window.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        
        /* wait until a certain time has passed before rendering the next frame */
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }

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
void Paddles::update(sf::Time deltaTime)
{
    /* handle player movement */
    sf::Vector2f playerMov (0.f, 0.f);
    // Debug
    // std::cerr << "Player Sprite: (" << playerSprite.getPosition().x << ", " << playerSprite.getPosition().y << ")" << std::endl;
    sf::Vector2f location = playerSprite.getPosition();
    if (playerUp && location.y > 0.f)
        playerMov.y -= playerSpeed;
    else if (playerDown && location.y < 380.f)
        playerMov.y += playerSpeed;

    playerSprite.move(playerMov * deltaTime.asSeconds());

    /* correct any overshoots in player position */
    location = playerSprite.getPosition();
    if (location.y < 0.f)
        playerSprite.setPosition(location.x, 0.f);
    else if (location.y > 380.f)
        playerSprite.setPosition(location.x, 380.f);


    /* move the ball according to its direction */
    ballSprite.move(ballDirection * deltaTime.asSeconds());
}

/* draws the images to the screen */
void Paddles::render()
{
    window.clear();
    window.draw(bgSprite);
    window.draw(playerSprite);
    window.draw(enemySprite);
    window.draw(ballSprite);
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

/* change direction from degrees to radians */
float Paddles::toRadians(float angle)
{
    return angle * (M_PI/180.f);
}
