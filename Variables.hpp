#ifndef __VARIABLES_HPP__
#define __VARIABLES_HPP__

#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include "Tile.hpp"
#include "Prop.hpp"
#include "TileMap.hpp"
#include "GuiType.hpp"

using json = nlohmann::json;

// Itt tárolom a globális változókat

namespace Variables {
    GuiType gui = GuiType::FŐMENÜ;
    int gameLevel = 0;
}

#endif // __VARIABLES_HPP__