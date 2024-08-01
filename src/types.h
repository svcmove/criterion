#pragma once

#include <cstdint>
#include <fstream>
#include <filesystem>
namespace criterion {
    class FileStream final : public std::fstream {
    public:
        explicit FileStream(const std::filesystem::path& input, const std::ios::openmode mode) :
            std::fstream(input, mode), path(input) {}
        explicit FileStream(const std::filesystem::path& input) :
            path(input) {}

        std::filesystem::path path;
    };
    class TaggedStream final : public std::stringstream {
        public:
        explicit TaggedStream(const std::filesystem::path& input) :
            path(input) {}
        std::filesystem::path path;
    };

    using u8 = std::uint8_t;
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;
    using i32 = std::int32_t;

    struct ChunkHeader {
        u32 type;
        u32 size;
        u32 marker;
    };
}
