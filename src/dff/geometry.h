#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <types.h>
namespace criterion::dff {
    class Geometry {
    public:
        explicit Geometry(FileStream& stream);
    private:
        struct {
            ChunkHeader chunk;
            ChunkHeader structure;
            u32 flags;
            u32 trianglesCount;
            u32 vertexCount;
            u32 morphTargetCount;
        } header;
        struct RenderTriangles {
            glm::vec3 xyz;
            u16 materialIndex;
        };

        std::vector<glm::vec3> colors;
        std::vector<glm::vec2> textCoords;
        std::vector<RenderTriangles> triangles;
    };
}