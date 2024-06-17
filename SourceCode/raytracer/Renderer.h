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

    }

private:
    const Camera& camera;
    // const Scene& scene; // TODO: Implement Scene class


};
