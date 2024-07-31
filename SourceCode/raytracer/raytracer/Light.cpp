#pragma warning( disable : 4365 )

#include <cmath>

#include "Light.h"
#include "CRTTypes.h"
#include "Scene.h"
#include "Scene.h"
#include "Globals.h"


Vec3 Light::lightContrib(const Scene& scene, const Vec3& point, const Vec3& normal) const {

    if (type == LightType::POINT) {
        Vec3 lightDir = (pos - point);
        float srSq = lightDir.lengthSquared(); // Sphere Radius Squared
        lightDir.normalize();
        float cosLaw = std::fabs(normal.dot(lightDir)); // fabs takes care of refractive materials
        float sa = 4 * PI * srSq; // Sphere Area
        Vec3 contrib = color * intensity * cosLaw / sa;
        float maxComponent = std::max({contrib.x, contrib.y, contrib.z});
        if (maxComponent < 0.05) {
            return {0.f, 0.f, 0.f};
        }

        if (scene.isOccluded(point, pos)) {
            return Vec3{ 0.f, 0.f, 0.f };
        }
        return contrib;
    }
    
    if (type == LightType::SUN) {
        Vec3 sunPos = point - direction * 1e+3f; // Assume 'direction' is normalized and set for the sun
        if (scene.isOccluded(point, sunPos)) {
            return Vec3{ 0.f, 0.f, 0.f };
        }

        // todo remove comments
        float cosLaw = std::fabs(normal.dot(direction)); // fabs takes care of refractive materials
        //float cosLaw = std::max(0.f, normal.dot(direction)); // Consider only the positive part
        Vec3 contrib = intensity * cosLaw * color; // No attenuation for directional light
        return contrib;
    }
    else { throw std::runtime_error("unknown light type"); }
}
