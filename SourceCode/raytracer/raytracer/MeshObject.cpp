#include "MeshObject.h"
#include "Triangle.h"
#include "Scene.h"

/* Construct a mesh object from a range of triangles. `l` and `u` inclusive. */

MeshObject::MeshObject(size_t l, size_t u) : SceneObject()
{
    triangleIndexes.reserve(u);
    for (size_t i = l; i <= u; i++)
    {
        triangleIndexes.push_back(i);
    }
}

MeshObject MeshObject::fromTriangles(const std::vector<size_t>& triangleIndexes)
{
    MeshObject meshObject = MeshObject(0, triangleIndexes.size() - 1);
    meshObject.triangleIndexes = triangleIndexes;
    return meshObject;
}

void MeshObject::translate(const std::vector<Triangle>& triangles, const Vec3& translation, std::vector<Vec3>& vertices)
{
    for (size_t i : triangleIndexes)
    {
        triangles[i].translate(translation, vertices);
    }
}

Material& MeshObject::getMaterial(Scene& scene) const
{
    Triangle& triangle = scene.triangles[triangleIndexes[0]];
    Material& material = scene.materials[triangle.materialIndex];
    return material;
}
