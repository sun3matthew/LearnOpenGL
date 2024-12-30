#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
private:
    unsigned int ID;
    int textureUnit;
    int width, height, nrChannels;

public:
    Texture(const char* path, bool alpha = false);
    void bind(int textureUnit);
    int getID();
    int getTextureUnit();
    int getWidth();
    int getHeight();
    int getNrChannels();
};

#endif