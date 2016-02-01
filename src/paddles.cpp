#include "paddles.hpp"

/*************
 * constants *
 *************/

const float Paddles::xRange = 640.f;
const float Paddles::yRange = 480.f;

const float Paddles::playerSpeed = 300.f;
const float Paddles::ballSpeed = 300.f;
const float Paddles::enemySpeed = 300.f;

const float Paddles::ballMaxAngle = 75.f;

const sf::Time Paddles::TimePerFrame = sf::seconds(1.f/60.f);

/****************
 * constructors *
 ****************/

/* basic constructor for the Paddles object */
Paddles::Paddles()
: window(sf::VideoMode(xRange, yRange), "Paddles")
, bgTexture()
, bgSprite()
, paddleTexture()
, playerSprite()
, enemySprite()
, playerUp(false)
, playerDown(false)
, ballTexture()
, ballSprite()
, ballDirection()
{
    /* disable v-sync */
    window.setVerticalSyncEnabled(false);

    loadTexture(bgSprite, bgTexture, "assets/images/paddlesBg.png");
    loadTexture(playerSprite, paddleTexture, "assets/images/player.png");
    loadTexture(enemySprite, paddleTexture, "assets/images/player.png");
    loadTexture(ballSprite, ballTexture, "assets/images/ball.png");

    /* place sprites */
    playerSprite.setPosition(50, 190); // Make these more general...
    enemySprite.setPosition(583, 190); //
    ballSprite.setPosition((xRange/2.f) - (ballTexture.getSize().x/2.f), yRange/2.f);

    /* set ball direction */
    ballDirection.x = 1; //cos(toRadians(30.f));
    ballDirection.y = -1.f * sin(toRadians(30.f));
}

/***********************
 * main game functions *
 ***********************/

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
        { timeSinceLastUpdate -= TimePerFrame;
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
    /* rewrite this MESS */

    /************************************************************/
    /* handle player movement */
    sf::Vector2f playerMov (0.f, 0.f);

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
    /*************************************************************/
    
    /* enemy logic */
    enemyAI(deltaTime);

    /* ball logic */
    moveBall(deltaTime);
    checkCollisions();
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
/******************
 * ball functions *
 ******************/

/* moves the ball */
void Paddles::moveBall(sf::Time deltaTime)
{
    sf::Vector2f ballMov = ballSpeed * ballDirection;
    ballSprite.move(ballMov * deltaTime.asSeconds());
    
    sf::Vector2f ballPosition = ballSprite.getPosition();

    /* correct the ball location */
    if (ballPosition.y < 0.f) 
        ballSprite.setPosition(ballPosition.x, 0.f);
    else if (ballPosition.y > yRange - 10.f) 
        ballSprite.setPosition(ballPosition.x, yRange - 10.f);
    else if (ballPosition.x < 0.f)
        ballSprite.setPosition(0.f, ballPosition.y);
    else if (ballPosition.x > xRange - 10.f)
        ballSprite.setPosition(xRange - 10.f, ballPosition.y);

    return;
}

void Paddles::checkCollisions()
{
    /* make sure that the ball stays within the acceptable range */
    sf::Vector2f ballPosition = ballSprite.getPosition();

    /* screen collision */
    if (ballPosition.y == 0.f || ballPosition.y == yRange - 10.f)
        ballDirection.y *= -1.f;
    else if (ballPosition.x == 0.f || ballPosition.x == xRange - 10.f)
        ballDirection.x *= -1.f;
    else if (playerSprite.getGlobalBounds().intersects(ballSprite.getGlobalBounds())) 
    {
        ballSprite.setPosition(playerSprite.getPosition().x + 7.f, ballPosition.y);
        bounceBall(playerSprite);
    }
    else if (enemySprite.getGlobalBounds().intersects(ballSprite.getGlobalBounds()))
    {
        ballSprite.setPosition(enemySprite.getPosition().x - 10.f, ballPosition.y);
        bounceBall(enemySprite);
    }

    return;
}

void Paddles::bounceBall(const sf::Sprite &sprite)
{
    float tempAngle = ((ballSprite.getPosition().y - sprite.getPosition().y) - (100.f / 2.f)) / (100.f / 2.f);
    tempAngle *= ballMaxAngle;

    ballDirection.y = toRadians(tempAngle);
    ballDirection.x *= -1;

    return;
}

/*******************
 * enemy functions *
 *******************/

/* moves the enemy based on the location of the ball */
void Paddles::enemyAI(sf::Time deltaTime)
{
    /* currently dumb as a sack of hammers */
    sf::Vector2f ballPosition = ballSprite.getPosition();
    sf::Vector2f enemyPosition = enemySprite.getPosition();

    /* move the enemy based on enemy location */
    sf::Vector2f enemyMov (0.f, 0.f);
    if (ballPosition.y < enemyPosition.y)
        enemyMov.y -= enemySpeed;
    else if (ballPosition.y > enemyPosition.y + 100.f)
        enemyMov.y += enemySpeed;

    enemySprite.move(enemyMov * deltaTime.asSeconds());

    /* correct the enemy position */
    enemyPosition = enemySprite.getPosition();
    if (enemyPosition.y < 0.f)
        enemySprite.setPosition(enemyPosition.x, 0.f);
    else if (enemyPosition.y > 380.f)
        enemySprite.setPosition(enemyPosition.x, 380.f);

    return;
}

/*************************
 * misc helper functions *
 *************************/

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

