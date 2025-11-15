#pragma once
#include "glm/glm.hpp"
#include <functional>

namespace Dogo {
    struct assimpVertex {
        glm::vec3 vertices;
        glm::vec3 normals;
        glm::vec2 texCoords;

        bool operator==(const assimpVertex& other) const {
            return vertices == other.vertices &&
                normals == other.normals &&
                texCoords == other.texCoords;
        }
    };

    template <typename T, typename... Rest>
    void hashCombine(std::size_t& seed, const T& v, const Rest&... rest) {
        seed ^= std::hash<T>{}(v)+0x9e3779b9 + (seed << 6) + (seed >> 2);
        (hashCombine(seed, rest), ...);
    }
}

namespace std {
    template <>
    struct hash<glm::vec3> {
        size_t operator()(const glm::vec3& vec) const {
            size_t seed = 0;
            Dogo::hashCombine(seed, vec.x, vec.y, vec.z);
            return seed;
        }
    };

    template <>
    struct hash<glm::vec2> {
        size_t operator()(const glm::vec2& vec) const {
            size_t seed = 0;
            Dogo::hashCombine(seed, vec.x, vec.y);
            return seed;
        }
    };

    template <>
    struct hash<Dogo::assimpVertex> {
        size_t operator()(const Dogo::assimpVertex& vertex) const {
            size_t seed = 0;
            Dogo::hashCombine(seed, vertex.vertices, vertex.normals, vertex.texCoords);
            return seed;
        }
    };
}
