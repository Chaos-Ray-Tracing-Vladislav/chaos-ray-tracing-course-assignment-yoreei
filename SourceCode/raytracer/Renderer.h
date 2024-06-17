#pragma once
#include "CRTTypes.h"
#include "Camera.h"
#include <tuple>
#include "perlin-noise.h"
#include <algorithm>

class Renderer {
public:
    Renderer(const Camera& camera)
        : camera(camera){}

    void render(Buffer2D& image) const
    {
        for (int y = 0; y < camera.getHeight(); ++y) {
            for (int x = 0; x < camera.getWidth(); ++x) {
                Ray ray = camera.generateRay(x, y);
                // Color color = traceImagePlane(ray); // hw3
                Color color = traceRay(ray); // hw5
                image(x, y) = color;
            }
        }
    }

private:
    const Camera& camera;
    // const Scene& scene; // TODO: Implement Scene class

    Color traceRay(const Ray& ray) const
    {
        
        // alls vertices even with the image plane
        // This one does not cause problems
        Triangle tri_even
        {
            Vec3{-1.f, -1.f, -1.f},
            Vec3{1.f, -1.f, -1.f},
            Vec3{0.f, 1.f, -1.f},
        };

        // Bottom vert deeper
        Triangle tri_bot
        {
            Vec3{-1.f, -1.f, -1.f},
            Vec3{1.f, -1.f, -1.f},
            Vec3{0.f, 1.f, -1.5f}
        };

        // right vert deeper
        Triangle tri_right
        {
            Vec3{-1.f, 1.f, -1.f},
            Vec3{-1.f, -1.f, -1.f},
            Vec3{1.f, 0.f, -1.5f},
        };

        // top vert deeper
        Triangle tri_top
        {
            Vec3{-1.f,1.f,-1.f},
            Vec3{0.f,1.f,-1.5f},
            Vec3{1.f,1.f,-1.f},
        };

        // left vert deeper
        Triangle tri_left
        {
            Vec3{1.f,1.f,-1.f},
            Vec3{-1.f,0.f,-1.5f},
            Vec3{1.f,-1.f,-1.f},
        };


        float t; Vec3 p;
        if (tri_left.intersect_plane2(ray, t, p)) {
            return shade_dbg_b(p);
        } else {
            return Color{0,0,0};
        }
    }

    /* hw3. For debugging */
    Color traceImagePlane(const Ray& ray) const
    {
        Vec3 p = ray.origin + ray.direction;
        float scale = -1.f / p.z;
        p = p * scale;
        return shade_abs(p);
    }

    Color shade_dbg_b(Vec3 p) const {
        uint8_t b = static_cast<uint8_t>(fabs(p.z + 1.0f) * 127.5f);
        return Color{ 5,5 , b };
    }

    Color shade_abs(Vec3 p) const {
        uint8_t r = static_cast<uint8_t>(fabs(p.x * 100.f));
        uint8_t g = static_cast<uint8_t>(fabs(p.y * 100.f));
        uint8_t b = static_cast<uint8_t>(fabs(p.z * 100.f));

        return Color{ r, g, b };
    }
};
