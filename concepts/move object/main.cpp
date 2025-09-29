#include <SFML/Graphics.hpp>

void boundObject(sf::CircleShape &circle, sf::Vector2u windowSize)
{
    sf::FloatRect bounds = circle.getGlobalBounds();
    if (bounds.top <= 0)
    {
        circle.setPosition(circle.getPosition().x, 0);
    }

    if (bounds.left <= 0)
    {
        circle.setPosition(0, circle.getPosition().y);
    }
    if ((bounds.top + bounds.height) >= windowSize.y)
    {
        circle.setPosition(circle.getPosition().x, windowSize.y - bounds.height);
    }

    if ((bounds.left + bounds.width) >= windowSize.x)
    {
        circle.setPosition(windowSize.x - bounds.width, circle.getPosition().y);
    }
}
void moveableObject(
    sf::CircleShape &circle,
    float speed,
    float dt,
    sf::Keyboard::Key left,
    sf::Keyboard::Key right,
    sf::Keyboard::Key up,
    sf::Keyboard::Key down,
    sf::Vector2u windowSize)
{
    boundObject(circle, windowSize);
    if (sf::Keyboard::isKeyPressed(left))
        circle.move(-speed * dt, 0.f);

    if (sf::Keyboard::isKeyPressed(right))
        circle.move(speed * dt, 0.f);

    if (sf::Keyboard::isKeyPressed(up))
        circle.move(0.f, -speed * dt);

    if (sf::Keyboard::isKeyPressed(down))
        circle.move(0.f, speed * dt);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "object move");
    sf::Vector2u windowSize = window.getSize();

    sf::CircleShape circle(25.f);
    sf::CircleShape ball(25.f);

    circle.setFillColor(sf::Color::Red);
    circle.setPosition(400, 300);
    ball.setFillColor(sf::Color::Blue);
    ball.setPosition(700, 50);

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        float dt = clock.restart().asSeconds();
        float speed = 300.f;

        moveableObject(circle, speed, dt, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down, windowSize);
        moveableObject(ball, speed, dt, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S, windowSize);

        window.clear();
        window.draw(ball);
        window.draw(circle);
        window.display();
    }
    return 0;
}