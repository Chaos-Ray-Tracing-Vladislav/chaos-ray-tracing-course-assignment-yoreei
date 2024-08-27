#include <stdexcept>
#include <string>
#include <cmath>

#include "include/Texture.h"
#include "include/TraceHit.h"
#include "include/Scene.h"

TextureType Texture::TypeFromString(const std::string& type)
{
    if (type == "albedo") {
        return TextureType::SOLID_COLOR;
    }
    else if (type == "edges") {
        return TextureType::EDGES;
    }
    else if (type == "checker") {
        return TextureType::CHECKER;
    }
    else if (type == "bitmap") {
        return TextureType::BITMAP;
    }
    else {
        throw std::runtime_error("Unknown texture type: " + type);
    }
}

Vec3 Texture::getAlbedo(const TraceHit& hit) const
{
    if (type == TextureType::SOLID_COLOR) {
        return color1;
    }
    else if (type == TextureType::EDGES) {
        float u = hit.baryU;
        float v = hit.baryV;
        if (u < textureSize || v < textureSize || 1 - u - v < textureSize) {
            return color1;
        }
        else {
            return color2;
        }
    }
    else if (type == TextureType::CHECKER) {
        float u = hit.u;
        float v = hit.v;
        float divCache = 0.5f / textureSize;
        u = u * divCache;
        v = v * divCache;
        float uFrac = fmod(u, 1.f);
        float vFrac = fmod(v, 1.f);

        return uFrac <= 0.5 && vFrac <= 0.5 ? color1 :
            uFrac > 0.5 && vFrac > 0.5 ? color1 :
            uFrac <= 0.5 && vFrac > 0.5 ? color2 :
            uFrac > 0.5 && vFrac <= 0.5 ? color2 :
            throw std::runtime_error("Texture::getAlbedo(): Checkerboard texture error");
    }
    else if (type == TextureType::BITMAP) {
        // TODO move this to Image
        float u = hit.u;
        float v = hit.v;
        const size_t width = bitmap.getWidth();
        const size_t height = bitmap.getHeight();
        size_t x = size_t(u * (float(width) - 1.f));
        size_t y = size_t(v * (float(height) - 1.f));
        // reverse top-bottom
        y = height - 1 - y;

        Color pixelColor = bitmap(x, y);

        return Vec3(pixelColor.r / 255.0f, pixelColor.g / 255.0f, pixelColor.b / 255.0f);
    }
    else { throw std::runtime_error("Texture::getAlbedo(): Unknown texture type"); }
}