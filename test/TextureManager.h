#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>

class TextureManager {
private:
    std::map<std::string, sf::Texture> textures;

public:
    sf::Texture& getTexture(const std::string& filename) {
        if (textures.find(filename) == textures.end()) {
            if (!textures[filename].loadFromFile(filename)) {
                std::cerr << "Error: Failed to load texture " << filename << std::endl;
            }
        }
        assert(textures.find(filename) != textures.end());
        return textures[filename];
    }
};