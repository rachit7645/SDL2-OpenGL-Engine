#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <vector>
#include <string_view>

#include <assimp/scene.h>

#include "Util.h"
#include "Mesh.h"
#include "MeshTextures.h"

namespace Renderer
{
    class Model
    {
    public:
        // Usings
        using TxPtr = std::shared_ptr<Texture>;
        // Main constructor
        Model(const std::string_view path, const MeshTextures& textures);
        // Data
        std::vector<Mesh> meshes;
    private:
        // Process each node recursively
        void ProcessNode
        (
            aiNode* node,
            const aiScene* scene,
            const MeshTextures& textures,
            const std::string& directory
        );
        // Process each mesh in the node
        Mesh ProcessMesh
        (
            aiMesh* mesh,
            const aiScene* scene,
            const MeshTextures& textures,
            const std::string& directory
        );
        // Process each texture in the mesh
        MeshTextures ProcessTextures
        (
            aiMesh* mesh,
            const aiScene* scene,
            const MeshTextures& pTextures,
            const std::string& directory
        );
    };
}

#endif