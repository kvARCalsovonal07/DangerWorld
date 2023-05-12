#ifndef __TILEMAP_HPP__
#define __TILEMAP_HPP__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include "Tile.hpp"
#include "Prop.hpp"

using json = nlohmann::json;

// A Tile Map class (A tile class magában nem szükséges itt használtam föl)
class TileMap : public sf::Drawable {
    public:
        // Konstruktor
        TileMap(json input) {
            // Tile Map intekben
            std::vector<std::vector<int>> tilemap;
            
            // Az int Tile Map kiszedése a json-ből
            for (int i = 0; i < input["Tile Map"].size(); i++) {
                std::vector<int> line;

                for (int j = 0; j < input["Tile Map"][i].size(); j++) {
                    line.push_back(input["Tile Map"][i][j]);
                }

                tilemap.push_back(line);
            }

            // Hozzáadni a játék objektumok listájához a játék legfontosabb elemeit, a tile-kat (a kockákat)
            for (int y = 0; y < tilemap.size(); y++) {
                for (int x = 0; x < tilemap[y].size(); x++) {
                    switch (tilemap[y][x]) {
                        case 0:
                            // Levegő

                            continue;
                        default:
                            // A png-k számoknak vannak elnevezve és azokat kell beírni.

                            // A tile létrehozása memória címkével mert anélkül nem működik (köszi sfml)
                            Tile* tile = new Tile("images/tileset/" + std::to_string(tilemap[y][x]) + ".png");
                            tile->setPosition(x * 32 * 2, y * 32 * 2);

                            // Hozzáadás
                            tiles.push_back(*tile);
                    }
                }
            }

            // Hozzáadni a díszelem listához a level json-ből kiszedett datákat
            for (int i = 0; i < input["Props"].size(); i++) {
                Prop* prop = new Prop(input["Props"][i]["Type"]);
                
                prop->setPosition(input["Props"][i]["Position"]["x"], input["Props"][i]["Position"]["y"]);
                prop->setScale(input["Props"][i]["Scale"]);
                prop->setRotation(input["Props"][i]["Rotation"]);
                prop->setOrigin(input["Props"][i]["Origin"]["x"], input["Props"][i]["Origin"]["y"]);

                props.push_back(*prop);
            }
        }
    
        // Editálás
        void update() {
            
        }

        // Kirajzolás
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            for (Tile tile : tiles) {
                target.draw(tile, states);
            }

            for (Prop prop : props) {
                target.draw(prop, states);
            }
        }
    private:
        // A változók

        int CameraX = 0;
        int CameraY = 0;

        int playerPosition = 0;

        std::vector<Tile> tiles;
        std::vector<Prop> props;
};

#endif // __TILEMAP_HPP__
