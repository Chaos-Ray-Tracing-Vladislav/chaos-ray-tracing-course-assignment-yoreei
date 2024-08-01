#pragma once
#include <vector>
#include <queue>

#include "include/CRTTypes.h"

enum class BlendType {
    NORMAL, /* Source Over */
    ADDITIVE,
};
/* A single ray's contribution to the final pixel color */
class Shade {
public:
    Vec3 color = { 0.f, 0.f, 0.f };
    float weight = 1.f;
    BlendType blendType = BlendType::NORMAL;
};

class Image;
using Shades = std::vector<Shade>;

class Settings;
/* Auxiliary Output. Records each shade's contribution to a pixel. `flatten(..)` to produce the final image. */
class ShadingSamples
{
public:
    ShadingSamples(size_t width, size_t height, const Settings* settings);

    /* @ouput image: flattened image */
    void flatten(Image& image);

    /* Output each depth as its own image. Useful for debugging */
    void slice(std::vector<Image>& images);
    void addSample(const TraceTask& task, const Vec3 color, BlendType blendType = BlendType::NORMAL);
    std::vector<Shades> pixels;
    size_t width;
    size_t height;
    const Settings* settings;
private:
    /* @brief max depth across all pixels */
    size_t pixelsMaxDepth();
};

