#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Danger World", sf::Style::Close);
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        if (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        window.clear(sf::Color::White);

        

        window.display();
    }
    
    return 0;
}
