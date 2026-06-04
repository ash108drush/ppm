#pragma once
#include "img_lib.h"

#include <filesystem>

namespace img_lib {
using Path = std::filesystem::path;

bool SavePPM(const Path& file, const Image& image);
Image LoadPPM(const Path& file);
void NegateInplace(img_lib::Image& image);
std::byte Negate(std::byte c);
}  // namespace img_lib
