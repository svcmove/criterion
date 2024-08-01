#include <vector>
#include <cstring>

#include <dff/clump.h>

namespace criterion::dff {
    GeometryList::GeometryList(FileStream& stream) {
        std::vector<char> buffer(sizeof(header));
        stream.read(&buffer[0], sizeof(header));

        std::memcpy(&header, &buffer[0], sizeof(header));
        for (i32 geometry{};
            geometry < header.geometryCount; geometry++) {

        }
    }

    Clump::Clump(FileStream& stream) {
        std::vector<char> buffer(sizeof(packet));
        stream.read(&buffer[0], sizeof(packet));

        std::memcpy(&packet, &buffer[0], sizeof(packet));

        ChunkHeader frameList;
        stream.read(&buffer[0], sizeof(frameList));
        std::memcpy(&frameList, &buffer[0], sizeof(frameList));

        // Let's skip the frame list for now
        stream.seekg(frameList.size, std::ios::cur);

        gList = GeometryList(stream);
    }
}
