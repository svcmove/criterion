#pragma once
#include <list>

#include <types.h>
namespace criterion::dff {

    class GeometryList {
    public:
        GeometryList() = default;
        explicit GeometryList(FileStream& stream);
    private:
        struct {
            ChunkHeader chunk;
            ChunkHeader structure;

            i32 geometryCount;
        } header;

        std::list<GeometryList> geometries;
    };

    class Clump {
    public:
        Clump() = default;
        explicit Clump(FileStream& stream);

    private:
        struct {
            ChunkHeader chunk;
            u32 atomicCount;
            u32 lightCount;
            u32 cameraCount;
        } packet;

        GeometryList gList;
    };
}
