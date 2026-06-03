#include "ppm_image.h"

#include <array>
#include <fstream>
#include <string_view>
#include <algorithm>

using namespace std;

namespace img_lib {

static const string_view PPM_SIG = "P6"sv;
static const int PPM_MAX = 255;

// реализуйте эту функцию самостоятельно
bool SavePPM(const Path& file, const Image& image){
    ofstream ofs(file, ios::binary);
    const int w = image.GetWidth();
    const int h = image.GetHeight();
    ofs << PPM_SIG << std::endl
        << w << ' '
        << h  << std::endl
        << PPM_MAX << std::endl;
    //std::vector<char> buff(image.GetWidth() * 3);
    int arr[3];
    for (int y = 0; y < h; ++y) {
        std::copy(image.GetLine(y), image.GetLine(y) + image.GetStep() *3, std::begin(arr));

    }

   /* for (int y = 0; y < h; ++y) {
        Color* line = result.GetLine(y);
        ifs.read(buff.data(), w * 3);

        for (int x = 0; x < w; ++x) {
            line[x].r = static_cast<char>(buff[x * 3 + 0]);
            line[x].g = static_cast<char>(buff[x * 3 + 1]);
            line[x].b = static_cast<char>(buff[x * 3 + 2]);
        }
    }
    */



    return false;
}

Image LoadPPM(const Path& file) {
    // открываем поток с флагом ios::binary
    // поскольку будем читать даные в двоичном формате
    ifstream ifs(file, ios::binary);
    std::string sign;
    int w, h, color_max;

    // читаем заголовок: он содержит формат, размеры изображения
    // и максимальное значение цвета
    ifs >> sign >> w >> h >> color_max;

    // мы поддерживаем изображения только формата P6
    // с максимальным значением цвета 255
    if (sign != PPM_SIG || color_max != PPM_MAX) {
        return {};
    }

    // пропускаем один байт - это конец строки
    const char next = ifs.get();
    if (next != '\n') {
        return {};
    }

    Image result(w, h, Color::Black());
    std::vector<char> buff(w * 3);

    for (int y = 0; y < h; ++y) {
        Color* line = result.GetLine(y);
        ifs.read(buff.data(), w * 3);

        for (int x = 0; x < w; ++x) {
            line[x].r = static_cast<byte>(buff[x * 3 + 0]);
            line[x].g = static_cast<byte>(buff[x * 3 + 1]);
            line[x].b = static_cast<byte>(buff[x * 3 + 2]);
        }
    }

    return result;
}

}  // namespace img_lib
