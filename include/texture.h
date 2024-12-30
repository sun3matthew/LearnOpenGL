#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture
{
private:
    unsigned int ID;
    int textureUnit;
    int width, height, nrChannels;

public:
    std::string type;
    std::string path;


    Texture(const char* path, bool alpha, std::string typeName);
    void bind(int textureUnit);
    int getID();
    int getTextureUnit();
    int getWidth();
    int getHeight();
    int getNrChannels();
};

#endif