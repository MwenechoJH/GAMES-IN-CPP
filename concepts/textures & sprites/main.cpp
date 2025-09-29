#include <SFML/Graphics.hpp>
#include <iostream>
void addAcceleration(float &obj_axis, float acc, float dt, int type, float speed)
{
    switch (type)
    {
    case 1:
    {
        if (obj_axis > 0)
        {
            obj_axis = -speed;
        }
        else
        {
            obj_axis -= acc * dt;
        }
        break;
    }
    case -1:
    {
        if (obj_axis < 0)
        {
            obj_axis = speed;
        }
        else
        {
            obj_axis += acc * dt;
        }
        break;
    }

    default:
        break;
    }
}
void boundObject(sf::Sprite &obj, sf::Vector2u windowSize, sf::Vector2f &obj_velocity, float dt)
{
    float gravity = 300.f;
    float resistance = 100.f;
    float bounce_ratio = -0.7;
    obj_velocity.y += gravity * dt;

    obj.move(obj_velocity * dt);

    sf::FloatRect bounds = obj.getGlobalBounds();

    if (bounds.top <= 30)
    {
        obj.setPosition(obj.getPosition().x, 30);
        obj_velocity.y = (bounce_ratio)*obj_velocity.y;
    }

    if (bounds.left <= 0)
    {
        obj.setPosition(0, obj.getPosition().y);
        obj_velocity.x = (bounce_ratio)*obj_velocity.x;
    }
    if ((bounds.top + bounds.height) >= windowSize.y)
    {
        obj.setPosition(obj.getPosition().x, windowSize.y - bounds.height);
        obj_velocity.y = (bounce_ratio)*obj_velocity.y;

        if (obj_velocity.x < 0)
        {
            obj_velocity.x += resistance * dt * 2;
        }
        else if (obj_velocity.x > 0)
        {
            obj_velocity.x -= resistance * dt * 2;
        }
    }

    if ((bounds.left + bounds.width) >= windowSize.x)
    {
        obj.setPosition(windowSize.x - bounds.width, obj.getPosition().y);
        obj_velocity.x = (bounce_ratio)*obj_velocity.x;
    }

    // air resistance
    if (obj_velocity.x < 0)
    {
        obj_velocity.x += resistance * dt * 0.3;
    }
    else if (obj_velocity.x > 0)
    {
        obj_velocity.x -= resistance * dt * 0.3;
    }
}
void moveableObject(
    sf::Sprite &obj,
    float speed,
    float dt,
    sf::Keyboard::Key left,
    sf::Keyboard::Key right,
    sf::Keyboard::Key up,
    sf::Keyboard::Key down,
    sf::Vector2u windowSize,
    sf::Vector2f &obj_velocity)
{
    float hor_acc = 300.f;

    boundObject(obj, windowSize, obj_velocity, dt);

    if (sf::Keyboard::isKeyPressed(left))
    {
        obj.move(-speed * dt, 0.f);
        addAcceleration(obj_velocity.x, hor_acc, dt, 1, speed);
    }

    if (sf::Keyboard::isKeyPressed(right))
    {
        obj.move(speed * dt, 0.f);
        addAcceleration(obj_velocity.x, hor_acc, dt, -1, speed);
    }

    if (sf::Keyboard::isKeyPressed(up))
    {
        obj.move(0.f, -speed * dt);
        addAcceleration(obj_velocity.y, hor_acc, dt, 1, speed);
    }

    if (sf::Keyboard::isKeyPressed(down))
    {
        obj.move(0.f, speed * dt);
        addAcceleration(obj_velocity.y, hor_acc, dt, -1, speed);
    }
}
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "sprites");
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2f obj_velocity(0.f, 0.f);
    sf::Clock clock;

    sf::Font font;
    if (!(font.loadFromFile("./assets/fonts/cubic.ttf")))
        std::cout << "cubic font not found" << std::endl;

    sf::Texture ball_texture;
    if (!(ball_texture.loadFromFile("./assets/textures/ball.png")))
        std::cout << "Ball Texture not Found" << std::endl;

    sf::Sprite ball;

    ball.setTexture(ball_texture);
    ball.setPosition(0, 500);
    ball.setScale(1.5f, 1.5f);

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);

    text.setString("Necho Bounce Game");
    text.setPosition(100, 5);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        float dt = clock.restart().asSeconds();
        float speed = 300.f;
        moveableObject(
            ball, speed, dt,
            sf::Keyboard::Left,
            sf::Keyboard::Right,
            sf::Keyboard::Up,
            sf::Keyboard::Down,
            windowSize,
            obj_velocity);

        window.clear(sf::Color::White);
        window.draw(text);
        window.draw(ball);
        window.display();
    }

    return 0;
}