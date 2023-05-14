#ifndef __MOB_HPP__
#define __MOB_HPP__

#include <iostream>
#include <SFML/Graphics.hpp>

// A Mob class
class Mob: public sf::Drawable {
    public:
        // Konstruktor
        Mob(bool flip, sf::RectangleShape hitbox, int health) {
            this->x = 0;
            this->y = 0;

            this->health = health;

            this->hitbox = hitbox;
            this->hitbox.setFillColor(sf::Color::Blue);

            this->flip = flip;
        }

        // Irány beállítása a felhasználónak
        void setFlip(bool flip) {
            this->flip = true;
        }

        // Az irány bekérése
        bool getFlip() {
            return this->flip;
        }

        // A hitbox megkapása a felhasználó számára
        sf::RectangleShape getHitbox() {
            return this->hitbox;
        }
        
        // A pozíció megkapása a felhasználónak
        sf::Vector2f getPosition() {
            return sf::Vector2f(this->x, this->y);
        }

        // Pozció beállítása a felhasználó számára
        void setPosition(int x, int y) {
            this->x = x;
            this->y = y;
        }

        // A hitboxal való érintkezés érzékelésének a megkönnyebbítése
        sf::FloatRect getGlobalBounds() {
            return hitbox.getGlobalBounds();
        }

        // Az élet mennyiségének megkapása a felhasználónak
        int getHealth() {
            return  this->health;
        }

    protected:
        // Váltizók

        bool flip;

        int x, y;
        int health;
        sf::RectangleShape hitbox;
        sf::Texture texture;
        sf::Sprite sprite;
};

#endif // __MOB_HPP__
