#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "prctc_game");
    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(200, 100);

    sf::RectangleShape rectangle(sf::Vector2f(100.f, 50.f));
    rectangle.setFillColor(sf::Color::Blue);
    rectangle.setPosition(400, 300);

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            float df = clock.restart().asSeconds();
            switch (event.type)
            {
            case sf::Event::Closed:
            {
                std::cout << "Closing Program";
                window.close();
                break;
            }

            case sf::Event::MouseButtonPressed:
            {
                std::cout << "mouse key pressed" << std::endl;
                if (event.mouseButton.button == 1)
                {
                    circle.setFillColor(sf::Color::Magenta);
                    circle.move(100.f * df, 0.f);
                }
                else
                {
                    circle.setFillColor(sf::Color::Blue);
                    circle.setPosition(100, 500);
                }
                break;
            }

            default:
                break;
            }
        }
        float df = clock.restart().asSeconds();
        circle.move(300.f * df, 0.f);
        window.clear();
        window.draw(circle);
        window.draw(rectangle);
        window.display();
    }

    return 0;
}