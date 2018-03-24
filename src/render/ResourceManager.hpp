#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <GL/glew.h>

#include <unordered_map>
#include <string>

class ResourceManager
{
private:
    static std::unordered_map<std::string, GLuint> loadedMap;
public:
    static void preLoadTexture(std::string path);
    static GLuint loadTexture(std::string path);
};

#endif
