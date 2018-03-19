#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <SDL.h>

#include <map>
#include <string>

class ResourceManager
{
private:
    static std::map<std::string, SDL_Texture*> loadedMap;
public:
    static SDL_Texture* loadTexture(std::string path);
};

#endif
