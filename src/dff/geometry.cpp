#include <cstring>
#include <dff/geometry.h>

namespace criterion::dff {
    Geometry::Geometry(FileStream& stream) {
        std::vector<char> buffer(sizeof(header));
        const auto position{stream.tellg()};
        stream.read(&buffer[0], sizeof(header));

        std::memcpy(&header, &buffer[0], sizeof(header));

        if (header.flags & 0x8) {
            for (u32 index{}; index < header.vertexCount; index++) {
                stream.read(&buffer[0], 4);
                colors.emplace_back(
                    static_cast<float>(buffer[0]),
                    static_cast<float>(buffer[1]),
                    static_cast<float>(buffer[2]));
            }
        }
        if (header.flags & 0xf || header.flags & 0x80) {
            for (u32 index{}; index < header.vertexCount; index++) {
                stream.read(&buffer[0], sizeof(glm::vec2));
                textCoords.emplace_back(
                    *reinterpret_cast<float*>(&buffer[0]),
                    *reinterpret_cast<float*>(&buffer[4]));
            }
        }

        RenderTriangles triangle{};
        for (u32 index{}; index < header.vertexCount; index++) {
            stream.read(&buffer[0], 8);
            triangle.xyz.x = *reinterpret_cast<u16*>(&buffer[0]);
            triangle.xyz.y = *reinterpret_cast<u16*>(&buffer[2]);
            triangle.xyz.z = *reinterpret_cast<u16*>(&buffer[4]);

            triangle.materialIndex = *reinterpret_cast<u16*>(&buffer[6]);
        }

        stream.seekg(position, std::ios::beg);
        stream.seekg(header.chunk.size, std::ios::cur);
    }
}
