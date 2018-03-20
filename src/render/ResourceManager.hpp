#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <SDL.h>

#include <unordered_map>
#include <string>

class ResourceManager
{
private:
    static std::unordered_map<std::string, SDL_Texture*> loadedMap;
public:
    static void preLoadTexture(std::string path);
    static SDL_Texture* loadTexture(std::string path);
};

#endif
