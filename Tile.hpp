#ifndef __TILE_HPP__
#define __TILE_HPP__

#include <iostream>
#include <SFML/Graphics.hpp>

class Tile : public sf::Drawable {
    public:

        // Konstruktor
        Tile(std::string textureFileName) {
            this->x = 0;
            this->y = 0;

            this->hitbox = sf::RectangleShape(sf::Vector2f(32 * 2, 32 * 2));
            this->hitbox.setFillColor(sf::Color::Green);
            this->hitbox.setPosition(this->x, this->y);
            
            this->texture.loadFromFile(textureFileName);

            this->sprite.setTexture(this->texture);
            this->sprite.setScale(2.0, 2.0);

        }

        // Kirajzolás
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            target.draw(sprite, states);
        }

        // Pozíció beállítása a felhasználónak
        void setPosition(int x, int y) {
            this->x = x;
            this->y = y;

            hitbox.setPosition(this->x, this->y);
            sprite.setPosition(this->x, this->y);
        }

        // Méret megkapása a felhasználónak
        sf::Vector2f getSize() {
            return hitbox.getSize();
        }

        // Érintkezés érzékelésének a megkönnyebbítése a felhasználónak
        sf::FloatRect getGlobalBounds() {
            return hitbox.getGlobalBounds();
        }

        // Pozíció megkapása a felhasználónak
        sf::Vector2f getPosition() {
            return sf::Vector2f(this->x, this->y);
        }

    private:
        // Változók

        int x, y;
        sf::RectangleShape hitbox;
        sf::Texture texture;
        sf::Sprite sprite;
};

#endif // __TILE_HPP__