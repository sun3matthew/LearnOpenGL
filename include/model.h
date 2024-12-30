#ifndef MODEL_H
#define MODEL_H

#include <shader.h>
#include <texture.h>
#include <mesh.h>

#include <vector>

#include <assimp/scene.h>


class Model 
{
    public:
        Model(char *path);
        void Draw(Shader &shader);	
    private:
        // model data
        std::vector<Mesh> meshes;
        std::string directory;
        std::vector<Texture> textures_loaded; 


        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                             std::string typeName);
};

#endif