//
// Created by vadim on 07.12.17.
//

#ifndef COMPUTERVISION_KERNELS_H
#define COMPUTERVISION_KERNELS_H
#include <cmath>
#include <algorithm>
#include <memory>

class Kernels {

protected:

    int height;

    int width;

    std::unique_ptr<double []> data;

public:

    Kernels(int height, int width, const double *data);

    Kernels();

    Kernels(const Kernels &kernel);

    Kernels(int height, int width);

    Kernels& operator=(const Kernels& kernel);

    Kernels(Kernels&& kernel) = default;

    Kernels& operator=(Kernels&& kernel) = default;

    std::pair<Kernels, Kernels> gaussian(float sigma);

    Kernels gaussian1d(float sigma, int size);

    std::pair<Kernels, Kernels> gaussian(float sigma, int size);

    Kernels transpose();

    double * getData();

    int getWidth();

    int getHeight();

    double getData(int x, int y);

    ~Kernels() = default;

    std::pair<Kernels, Kernels> sobelX();

    std::pair<Kernels, Kernels> sobelY();
};


#endif //COMPUTERVISION_KERNELS_H
