#include "paddles.hpp"

const float Paddles::playerSpeed = 300.f;
const float Paddles::ballSpeed = 350.f;
const float Paddles::enemySpeed = 300.f;
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
    bounceBall(deltaTime);

    /* the enemy moves! */
    enemyAI(deltaTime);

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

/* collision detection for the ball sprite */
void Paddles::bounceBall(sf::Time deltaTime)
{
    sf::Vector2f ballLocation = ballSprite.getPosition();

    /* check if the ball has collided with the screen */
    if (ballLocation.y == 0.f || ballLocation.y == 470.f)
        ballDirection.y *= -1.f;
    else if (ballLocation.x == 0.f || ballLocation.x == 630.f)
        ballDirection.x *= -1.f;

    /* move the ball */
    ballSprite.move(ballDirection * deltaTime.asSeconds());
    bool entityCollision = playerSprite.getGlobalBounds().intersects(ballSprite.getGlobalBounds())
                            || enemySprite.getGlobalBounds().intersects(ballSprite.getGlobalBounds());

    /* correct the ball's position if it moved too far */
    if (ballLocation.y < 0.f || ballLocation.y > 470.f)
    {
        if (ballLocation.y < 0.f)
            ballSprite.setPosition(ballLocation.x, 0);
        else
            ballSprite.setPosition(ballLocation.x, 470);
    }
    else if (ballLocation.x < 0.f || ballLocation.x > 630.f)
    {
        if (ballLocation.x < 0.f)
            ballSprite.setPosition(0.f, ballLocation.y);
        else
            ballSprite.setPosition(630.f, ballLocation.y);
    }
    else if (entityCollision)
    {
        ballDirection.x *= -1.f;
    }

    return;
}

/* Determines where the enemy will move*/
void Paddles::enemyAI(sf::Time deltaTime)
{
    /* dumb as a sack of hammers right now */
    sf::Vector2f ballLocation = ballSprite.getPosition();
    sf::Vector2f enemyLocation = enemySprite.getPosition();
    sf::Vector2f enemyMov (0.f, 0.f);

    if (ballLocation.y > (enemyLocation.y + 50)) 
        enemyMov.y += enemySpeed;
    else if (ballLocation.y < (enemyLocation.y + 50))
        enemyMov.y -= enemySpeed;

    enemySprite.move(enemyMov * deltaTime.asSeconds());

    return;
}
