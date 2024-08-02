#pragma once
#include <glm/glm.hpp>

#include <types.h>
namespace criterion::dff {

    class Frames {
    public:
        explicit Frames(FileStream& stream);

    private:
        struct Model {
            glm::vec3 rot1;
            glm::vec3 rot2;
            glm::vec3 rot3;
            glm::vec3 position;
            u32 parent;
            u32 flags;

            std::array<u8, 12> pad;
        } model;

        static_assert(sizeof(glm::vec3) == sizeof(float) * 3, "");
    };
}