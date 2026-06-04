#include "ppm_image.h"


#include <fstream>
#include <string_view>

using namespace std;

namespace img_lib {

static const string_view PPM_SIG = "P6"sv;
static const int PPM_MAX = 255;

// реализуйте эту функцию самостоятельно
bool SavePPM(const Path& file, const Image& image){
    ofstream ofs(file, ios::binary);
    if (!ofs) {
        return false;
    }
    const int w = image.GetWidth();
    const int h = image.GetHeight();
    const int step = image.GetStep();
    ofs << PPM_SIG << '\n'
        << w << ' '
        << h  << '\n'
        << PPM_MAX << '\n';
    //std::vector<byte> buff(image.GetWidth() * 3);
    //std::array<byte> buf[1024];
    const Color* begin = image.GetLine(0);
    for (int y = 0; y < h; ++y) {
        std::vector<char> buff(w * 3);
        std::fill(buff.begin(),buff.end(),static_cast<char>(std::byte{0}));
        for(int x = 0; x < w *3 ;++x ){
            if(x < w){
                const Color* pixel = reinterpret_cast<const Color*>(begin + (y * step +x));
                buff[x * 3 + 0] = (static_cast<char>(pixel->r));
                buff[x * 3  + 1] = (static_cast<char>(pixel->g));
                buff[x * 3 + 2] = (static_cast<char>(pixel->b));
            }

        } //end x
        ofs.write(buff.data(), buff.size());
    } //end y
    ofs.close();
    return true;
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

void NegateInplace(Image &image){
    const int w = image.GetWidth();
    const int h = image.GetHeight();
    const int step = image.GetStep();

    //std::vector<byte> buff(image.GetWidth() * 3);
    //std::array<byte> buf[1024];
    Color* begin = image.GetLine(0);
    for (int y = 0; y < h; ++y) {
        //std::vector<char> buff(w * 3);
       // std::fill(buff.begin(),buff.end(),static_cast<char>(std::byte{0}));
        for(int x = 0; x < w  ;++x ){
            if(x < w){
                Color* pixel = reinterpret_cast<Color*>(begin + (y * step +x));
                pixel->r = Negate(pixel->r);
                pixel->g = Negate(pixel->r);
                pixel->b = Negate(pixel->r);
            }

        } //end x
        //ofs.write(buff.data(), buff.size());
    } //end y
}

std::byte Negate(std::byte c) {
    return static_cast<std::byte>(255 - to_integer<int>(c));
}

}  // namespace img_lib
