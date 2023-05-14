#ifndef __SKELETON_HPP__
#define __SKELETON_HPP__

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Mob.hpp"
#include "Tile.hpp"

class Skeleton : public Mob {
    public:

        // Konstruktor
        Skeleton(bool flip) : Mob(flip, sf::RectangleShape(sf::Vector2f(40, 100)), 50) {
            this->texture.loadFromFile("images/mobs/skeleton.png");

            this->sprite.setTexture(this->texture);
            this->sprite.setScale(sf::Vector2f(2.0, 2.0));

            this->animationFrame = 0;
            this->animationSleep = 0;
            this->action = 1;
            this->attackingCooldown = 50;
            this->attacking = false;
            this->takeHit = false;
            this->alive = true;
            this->dy = 0;

            this->attackingArea = sf::RectangleShape(sf::Vector2f(120, 100));
            this->attackingArea.setFillColor(sf::Color(255, 0, 0, 150));
        }

        // Mozgás
        void move(std::vector<Tile> &tiles) {
            this->hitbox.setPosition(this->x, this->y);
            this->sprite.setPosition(this->x - 130, this->y - 102);
            this->attackingArea.setPosition(this->x - 40, this->y);

            dy += 0.4;
            y += dy;

            // Platformer Fizika
            for (int i = 0; i < tiles.size(); i++) {
                if (hitbox.getGlobalBounds().intersects(tiles[i].getGlobalBounds())) {
                    sf::FloatRect intersection;
                    hitbox.getGlobalBounds().intersects(tiles[i].getGlobalBounds(), intersection);

                    if (intersection.width > intersection.height) {
                        if (y < tiles[i].getPosition().y) {
                            dy = 0;
                            y = tiles[i].getPosition().y - this->hitbox.getSize().y + 1;
                        } else {
                            dy = 0;
                            y = tiles[i].getPosition().y + tiles[i].getSize().y + 1;
                        }
                    } else {
                        if (y > tiles[i].getPosition().y - this->hitbox.getSize().y + 1) {
                            if (x < tiles[i].getPosition().x) {
                                if (attackingCooldown == 0) {
                                    flip = true;
                                }
                            } else {
                                if (attackingCooldown == 0) {
                                    flip = false;
                                }
                            }
                        }
                    }
                }
            }

            // Jobbra ballra mozgás és ütés
            if (alive) {
                if (!attacking && attackingCooldown < 1 && !takeHit) {
                    if (flip) {
                        x -= 3;
                    } else {
                        x += 3;
                    }

                    // Ütés
                }
            }

            // Fejlesztői ezközök
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                this->flip = true;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                this->flip = false;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                kill();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                startAttack();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                damage(10);
            }
        }

        // Animáció
        void update() {
            if (attackingCooldown > 0) {
                attackingCooldown--;
            }

            // A cselekvések kezelése
            if (alive) {
                if (attacking) {
                    action = 2;
                }

                if (attackingCooldown > 0 && !attacking) {
                    action = 0;
                }
                if (!attacking && attackingCooldown < 1 && !takeHit) {
                    action = 1;
                }

                if (takeHit) {
                    action = 3;
                    attacking = false;
                }

                if (this->health < 1) {
                    animationFrame  = 0;
                    animationSleep = 0;
                    alive = false;
                }
            } else {
                action = 4;
                attacking = false;
            }

            // Animációk kezelése
            switch (action) {
                case 0:
                    animationSleep++;
                    if (animationSleep > 5) {
                        animationSleep = 0;

                        animationFrame++;
                        if (animationFrame > 3) {
                            animationFrame = 0;
                        }                       
                    }
                    break;
                case 1:
                    animationSleep++;
                    if (animationSleep > 5) {
                        animationSleep = 0;

                        animationFrame++;
                        if (animationFrame > 3) {
                            animationFrame = 0;
                        }                       
                    }
                    break;
                case 2:
                    animationSleep++;
                    if (animationSleep > 5) {
                        animationSleep = 0;

                        if (animationFrame == 6) {
                            attack();
                        }

                        animationFrame++;
                        if (animationFrame > 7) {
                            animationFrame = 0;

                            action = 0;
                            attacking = false;
                        }
                    }
                    break;
                case 3:
                    animationSleep++;
                    if (animationSleep > 5) {
                        animationSleep = 0;

                        animationFrame++;
                        if (animationFrame > 3) {
                            animationFrame = 0;

                            action = 0;
                            takeHit = false;
                        }
                    }
                    break;
                case 4:
                    if (animationFrame < 3) {
                        animationSleep++;
                        if (animationSleep > 3) {
                            animationSleep = 0;

                            animationFrame++;
                        }
                    }
                    break;
            }

            // A sprite forgatása és a frame kivágása
            if (!flip) {
                sprite.setTextureRect(sf::IntRect(animationFrame * 150, action * 150, 150, 150));
            } else {
                sprite.setTextureRect(sf::IntRect(animationFrame * 150 + 150, action * 150, -150, 150));
            }
        }

        // Kirajzolás
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            target.draw(this->attackingArea, states);
            target.draw(this->hitbox, states);
            target.draw(this->sprite, states);
        }

        // Sebzés a külső felhasználóknak
        void damage(int damage) {
            if (alive && !takeHit) {
                this->takeHit = true;
                this->animationFrame = 0;
                this->animationSleep = 0;

                this->health -= damage;
            }
        }

        // A mob kivégzése a felhasználó számára
        void kill() {
            if (alive) {
                this->animationFrame = 0;
                this->animationSleep = 0;
                this->alive = false;
            }
        }

    private:
        // Itteni változók

        int animationFrame;
        int animationSleep;
        int action;
        int attackingCooldown;
        bool alive;
        bool defaultFlip;
        bool attacking;
        bool takeHit;
        float dy;

        sf::RectangleShape attackingArea;

        // Mob Változók

        // int x, y;
        // int health;
        // sf::RectangleShape hitbox;
        // sf::Texture texture;
        // sf::Sprite sprite;

        // Az ütés kezdete
        void startAttack() {
            if (!attacking && alive && attackingCooldown < 1 && !takeHit) {
                attackingCooldown = 100;
                attacking = true;
                animationFrame = 0;
                animationSleep = 0;
            }
        }

        // Az ütés
        void attack() {
            sf::RectangleShape attackingRect(sf::Vector2f(120, this->hitbox.getSize().y));
            attackingRect.setFillColor(sf::Color::Green);

            if (flip) {
                attackingRect.setPosition(this->x - attackingRect.getSize().x, this->y);
            } else {
                attackingRect.setPosition(this->x + hitbox.getSize().x, this->y);
            }

            // Érintkezés
        }
};

#endif // __SKELETON_HPP__
