#include <vector>
#include <cstring>
#include <txd/textures_container.h>

namespace criterion::txd {
    TexturesContainer::TexturesContainer(FileStream& stream) {
        std::vector<char> buffer(sizeof(container));
        stream.read(&buffer[0], sizeof(container));

        std::memcpy(&container, &buffer[0], sizeof(container));

        for (u32 index{}; index < container.count ; ++index) {
            textures.emplace_back(stream);
        }
    }

    std::vector<TextureTaggedData> TexturesContainer::collect() const {
        std::vector<TextureTaggedData> result;
        for (const auto& texture : textures) {
            result.emplace_back(texture.getName(), texture.getData(true));
        }
        return result;
    }
}
