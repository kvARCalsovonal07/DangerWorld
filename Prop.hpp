#ifndef __PROP_HPP__
#define __PROP_HPP__

#include <iostream>
#include <SFML/Graphics.hpp>

// A Díszelemek
class Prop : public sf::Drawable {
    public:
        // Konstruktor
        Prop(std::string propType) {
            this->texture.loadFromFile("images/props/" + propType + ".png");

            this->sprite.setTexture(this->texture);

            this->x = 0;
            this->y = 0;
        }

        // Méret szorzó beállítása a felhasznnálónak
        void setScale(float scale) {
            this->sprite.setScale(sf::Vector2f(scale, scale));
        }

        // Rotáció (forgás) beállítása a felhasználónak
        void setRotation(int rotation) {
            this->sprite.setRotation(rotation);
        }

        // Forgás középpontjának beállítása a felhasznzálónak
        void setOrigin(int x, int y) {
            this->sprite.setOrigin(sf::Vector2f(x, y));
        }

        // Pozíció beállítása a felhasználónak
        void setPosition(int x, int y) {
            this->sprite.setPosition(this->x, this->y);
        }

        // Pozíció lekérése a felhasználónak
        sf::Vector2f getPosition() {
            return sf::Vector2f(this->x, this->y);
        }

        // Kirajzolás
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            target.draw(this->sprite, states);
        }
    private:
        // Változók

        int x, y;
        sf::Texture texture;
        sf::Sprite sprite;
};

#endif // __PROP_HPP__
