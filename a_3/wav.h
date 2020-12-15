#define _USE_MATH_DEFINES

#include <vector>
#include <string>
#include <complex>
#include <cmath>
#include "wavheader.h"

const std::string COMPRESS_ERROR = "Degree should be a double in range [0, 1]!\n";

typedef std::complex<double> complex;

class CWAV {
public:
    void write(const std::string &filename);
    CWAV(const std::string& filename);
    void compress(double degree);
    ~CWAV();

private:
    WAVHEADER header;
    char *data;
    void getComplexData(std::vector<complex> &cdata);
    void updateData(const std::vector<complex> &cdata);
    void transform(std::vector<complex> &array, bool is_inverted);
};
