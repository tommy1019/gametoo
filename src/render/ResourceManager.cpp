#include "ResourceManager.hpp"

#include "../GameManager.hpp"

#include <iostream>

#include <SDL_image.h>

std::unordered_map<std::string, SDL_Texture*> ResourceManager::loadedMap;

void ResourceManager::preLoadTexture(std::string path)
{
    loadTexture(path);
}

SDL_Texture* ResourceManager::loadTexture(std::string path)
{
    if (loadedMap.count(path) > 0)
    {
        return loadedMap.at(path);
    }

    SDL_Texture* texture;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr)
    {
        std::cout << "Unable to load image: " << path << std::endl;
        std::cout << IMG_GetError() << std::endl;
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(GameManager::renderer, loadedSurface);
        if (texture == nullptr)
        {
            std::cout << "Failed to create texture: " << path << std::endl;
            std::cout << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(loadedSurface);
    }
    loadedMap.insert(std::pair<std::string, SDL_Texture*>(path, texture));

    return texture;
}
