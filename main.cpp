#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <nlohmann/json.hpp>
#include <map>
#include <fstream>

#include "Tile.hpp"
#include "TileMap.hpp"
#include "GuiType.hpp"
#include "Variables.hpp"

using json = nlohmann::json;

// Kis segítség a json bekéréséhez
json loadJson(std::string fileName) {
    std::ifstream ifstr(fileName);
    json loadedJson;

    ifstr >> loadedJson;

    return loadedJson;
}

// Kis segítség a json elmetéséhez
void saveJson(json &input, std::string fileName) {
    std::ofstream o(fileName);
    o << std::setw(4) << input << std::endl;
}

int main() {
    
    // Az ablak
    sf::RenderWindow window(sf::VideoMode(25 * 32 * 2, 15 * 32 * 2), "Danger World", sf::Style::Close);
    window.setFramerateLimit(60);

    // A config json
    json config = loadJson("config.json");

    // A mapok listája
    std::vector<TileMap> maps;
    
    // A mapok hozzáadása a listához
    for (int i = 0; i < config["levels"]; i++) {
        json levelJson = loadJson("levels/" + std::to_string(i + 1) + ".json");

        TileMap level(levelJson);

        maps.push_back(level);
    }

    // A játék ciklus
    while (window.isOpen()) {

        // A bezárás event érzékelése
        sf::Event event;
        if (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Ide kellenek majd a külömböző gui típusok
        switch (Variables::gui) {
            // Főmenü
            case GuiType::FŐMENÜ:
                window.clear(sf::Color::White);
                break;
            // Készítők menü
            case GuiType::KÉSZÍTŐK:
                window.clear(sf::Color::White);
                break;
            // Maga a játék
            case GuiType::JÁTÉK:
                window.clear(sf::Color::Black);

                window.draw(maps[0]);

                break;
        }

        window.display();
    }
    
    return 0;
}