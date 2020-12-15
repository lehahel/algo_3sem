#include "wav.h"

CWAV::CWAV(const std::string &filename) {
    FILE *file = fopen(filename.c_str(), "rb");
    fread(&header, sizeof(WAVHEADER), 1, file);
    printWAVHeader(header);
    data = new char[header.subchunk2Size];
    fread(data, header.subchunk2Size, 1, file);
    fclose(file);
}

CWAV::~CWAV() {
    delete[] data;
}

void CWAV::write(const std::string &filename) {
    FILE *file = fopen(filename.c_str(), "wb");
    fwrite(&header, sizeof(WAVHEADER), 1, file);
    fwrite(data, header.subchunk2Size, 1, file);
    fclose(file);
}

void CWAV::getComplexData(std::vector<complex> &cdata) {
    int log_data = 1;
    while (log_data < header.subchunk2Size) {
        log_data <<= 1;
    }
    cdata.resize(log_data);
    for (size_t i = 0; i < header.subchunk2Size; ++i) {
        cdata[i] = complex(data[i]);
    }
}

void CWAV::updateData(const std::vector<complex> &cdata) {
    for (size_t i = 0; i < header.subchunk2Size; ++i) {
        data[i] = static_cast<char>(cdata[i].real());
    }
}

void CWAV::compress(double degree) {
    if (degree < 0 || degree > 1) {
        std::cout << COMPRESS_ERROR;
        return;
    }
    std::vector<complex> cdata;
    getComplexData(cdata);

    transform(cdata, false);

    for (int i = static_cast<int>(cdata.size() * degree); i < cdata.size(); ++i) {
        cdata[i] = 0;
    }

    transform(cdata, true);

    updateData(cdata);
}

void CWAV::transform(std::vector<std::complex<double>> &array, bool is_inverted) {
    size_t n = array.size();
    if (n == 1) {
        return;
    }

    std::vector<std::complex<double>> left(n / 2);
    std::vector<std::complex<double>> right(n / 2);
    
    for (int i = 0, j = 0; i < n; i += 2, ++j) {
        left[j] = array[i];
        right[j] = array[i + 1];
    }

    transform(left, is_inverted);
    transform(right, is_inverted);

    double angle = (2 * M_PI / n) * (is_inverted ? -1 : 1);
    std::complex<double> w(1);
    std::complex<double> wn(cos(angle), sin(angle));

    for (int i = 0; i < n / 2; ++i) {
        array[i] = left[i] + w * right[i];
        array[i + n / 2] = left[i] - w * right[i];
        if (is_inverted) {
            array[i] /= 2;
            array[i + n / 2] /= 2;
        }
        w *= wn;
    }
}