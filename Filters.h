//
// Created by vadim on 06.12.17.
//

#ifndef COMPUTERVISION_FILTERS_H
#define COMPUTERVISION_FILTERS_H


#include "Image.h"
#include "Kernels.h"

class Filters {

public:
//    typedef std::function<Image(Image&, Image&)> SobelFunction;

    Image gaussian(Image &src, float sigma, BorderTypes border);

    Image convolve(Image src, Kernels &kernel, BorderTypes border);

    std::pair<Image, Image> sobel(Image &src, BorderTypes border);

    Image magnitude(Image &dx, Image &dy);

    double magnitudeVal(double dx, double dy);

    Image sobel(Image &src, BorderTypes border, int type);
};


#endif //COMPUTERVISION_FILTERS_H
