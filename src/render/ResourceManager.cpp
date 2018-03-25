#include "ResourceManager.hpp"

#include <iostream>

#include <SDL_image.h>

#include "../GameManager.hpp"

std::unordered_map<std::string, GLuint> ResourceManager::loadedMap;

void ResourceManager::preLoadTexture(std::string path)
{
    loadTexture(path);
}

GLuint ResourceManager::loadTexture(std::string path)
{
    if (loadedMap.count(path) > 0)
    {
        return loadedMap.at(path);
    }

    GLuint loadedTexture;

    glGenTextures(1, &loadedTexture);
    glBindTexture(GL_TEXTURE_2D, loadedTexture);

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr)
    {
        std::cout << "Unable to load image: " << path << std::endl;
        std::cout << IMG_GetError() << std::endl;
    }
    else
    {
        GLenum textureFormat = 0;
        GLint  numberColors;

        numberColors = loadedSurface->format->BytesPerPixel;
        if(numberColors == 4)
        {
            if(loadedSurface->format->Rmask == 0x000000ff)
                textureFormat = GL_RGBA;
            else
                textureFormat = GL_BGRA;
        }
        else if(numberColors == 3)
        {
            if(loadedSurface->format->Rmask == 0x000000ff)
                textureFormat = GL_RGB;
            else
                textureFormat = GL_BGR;
        }
        else
        {
            std::cout << "Image is not truecolor" << std::endl;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, numberColors, loadedSurface->w, loadedSurface->h, 0, textureFormat, GL_UNSIGNED_BYTE, loadedSurface->pixels);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    SDL_FreeSurface(loadedSurface);

    loadedMap.insert(std::pair<std::string, GLuint>(path, loadedTexture));

    return loadedTexture;
}

void ResourceManager::unloadTexture(GLuint texture)
{
    std::cout << "Still not unloading textures" << std::endl;
}
