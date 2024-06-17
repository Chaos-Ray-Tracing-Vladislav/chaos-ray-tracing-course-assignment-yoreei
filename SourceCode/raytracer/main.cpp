#include <fstream>
#include <cstdint>
#include <memory>
#include <string>

#include "CRTTypes.h"
#include "Renderer.h"
#include "hw4.h"

/// Output image resolution
static const int maxColorComponent = 255;

void save_ppm(Buffer2D& buf)
{
    std::ofstream ppmFileStream("crt_output_image.ppm", std::ios::out | std::ios::binary);
    ppmFileStream << "P3\n"; ppmFileStream << buf.width << " " << buf.height << "\n";
    ppmFileStream << maxColorComponent << "\n";

    for (int rowIdx = 0; rowIdx < buf.height; ++rowIdx) {
        for (int colIdx = 0; colIdx < buf.width; ++colIdx) {
            const Color& Color = buf.data[rowIdx * buf.width + colIdx];
            ppmFileStream << (int)Color.r << " " << (int)Color.g << " " << (int)Color.b << "\t";
        }
        ppmFileStream << "\n";
    }

    ppmFileStream.close();
}

int main()
{
    uint16_t width = 2, height = 2;
    Vec3 camUp = {0.f,1.f,0.f};
    Vec3 camPos = {0.f,0.f,0.f};
    Vec3 camDir = {0.f,0.f,-1.f};

    Buffer2D buf = {width, height};
    Camera cam = {width, height, 90.f, camPos, camDir, camUp};
    Renderer renderer {cam};
    renderer.render(buf);
    save_ppm(buf);
    return 0;
}
