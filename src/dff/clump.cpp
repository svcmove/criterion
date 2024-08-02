#include <vector>
#include <cstring>

#include <dff/clump.h>

namespace criterion::dff {
    FrameList::FrameList(FileStream& stream) {
        std::vector<char> buffer(sizeof(header));
        stream.read(&buffer[0], sizeof(header));

        std::memcpy(&header, &buffer[0], sizeof(header));
        for (i32 frame{}; frame < header.frames; frame++) {
            frames.emplace_back(stream);
        }

        ChunkHeader extension;
        stream.readsome(&buffer[0], sizeof(extension));
        std::memcpy(&extension, &buffer[0], sizeof(extension));

        if (extension.type == 3) {
            stream.seekg(extension.size, std::ios::cur);
        }
    }

    GeometryList::GeometryList(FileStream& stream) {
        std::vector<char> buffer(sizeof(header));
        stream.read(&buffer[0], sizeof(header));

        std::memcpy(&header, &buffer[0], sizeof(header));
        for (i32 geometry{};
            geometry < header.geometryCount; geometry++) {
            geometries.emplace_back(stream);
        }
    }

    Clump::Clump(FileStream& stream) {
        std::vector<char> buffer(sizeof(packet));
        stream.read(&buffer[0], sizeof(packet));

        std::memcpy(&packet, &buffer[0], sizeof(packet));

        // Let's skip the frame list for now
        frames = FrameList(stream);

        geoPack = GeometryList(stream);
    }
}
