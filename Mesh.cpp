#include "Mesh.h"

// Using namespaces
using namespace Renderer;

// Usings
using Maths::AABB;

Mesh::Mesh
(
    const std::vector<Vertex>& vertices,
    const std::vector<u32>& indices,
    const MeshTextures& textures,
    const AABB& aabb
)
    : vao(std::make_shared<VertexArray>(vertices, indices)),
      textures(textures),
      aabb(aabb)
{
}