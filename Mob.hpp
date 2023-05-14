#ifndef __MOB_HPP__
#define __MOB_HPP__

#include <iostream>
#include <SFML/Graphics.hpp>

// A Mob Típus enumja
enum MobType {
    SKELETON,
    MUSHROOM
};

// A Mob class
class Mob: public sf::Drawable {
    public:
        // Konstruktor
        Mob(sf::RectangleShape hitbox, int health) {
            this->x = 0;
            this->y = 0;

            this->health = health;

            this->hitbox = hitbox;
            this->hitbox.setFillColor(sf::Color::Blue);
        }

        sf::RectangleShape getHitbox() {
            return this->hitbox;
        }

        sf::Vector2f getPosition() {
            return sf::Vector2f(this->x, this->y);
        }

        int getHealth() {
            return  this->health;
        }

    protected:
        // Váltizók

        int x, y;
        int health;
        sf::RectangleShape hitbox;
        sf::Texture texture;
        sf::Sprite sprite;
};

#endif // __MOB_HPP__