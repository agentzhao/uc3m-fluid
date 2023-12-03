#ifndef HASH_HPP
#define HASH_HPP

#include <cstdint>
#include <vector>

namespace hashing {

struct vHash {
  auto operator()(const std::vector<int> &vector) const {
    const int six = 6;
    const uint32_t GoldenRatioInitValue = 0x9e3779b9;

    auto hash = vector.size();
    for (const auto &element : vector) {
      hash ^= element + GoldenRatioInitValue + (hash << six) + (hash >> 2);
    }
    return hash;
  }
};

} // namespace hashing

#endif // HASHING_HPP
