#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "prctc_game");

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
            {
                std::cout << "Closing Program";
                window.close();
                break;
            }

            case sf::Event::KeyPressed:
            {
                std::cout << "Key pressed";
                std::cout << event.key.code << std::endl;
                break;
            }

            case sf::Event::MouseMoved:
            {
                std::cout << "Mouse x: " << event.mouseMove.x << " y: " << event.mouseMove.y << std::endl;
                break;
            }

            case sf::Event::MouseButtonPressed:
            {
                std::cout << ((event.mouseButton.button == 1) ? "Right Click" : "Left Click") << std::endl;
                std::cout << "Mouse Clicked at: " << event.mouseButton.x << "y: " << event.mouseButton.y << std::endl;
            }
            default:
                continue;
            }
        }
        window.clear();
        window.display();
    }

    return 0;
}