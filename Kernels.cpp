//
// Created by vadim on 07.12.17.
//

#include <assert.h>
#include <iostream>
#include "Kernels.h"


Kernels::Kernels(int height, int width) {
    assert(width > 0 && height > 0);

    this->width = width;
    this->height = height;
    data = std::make_unique<double[]>(width * height);
}

Kernels::Kernels(int height, int width, const double *data)
        : Kernels(height, width) {
    std::copy(data, data + height * width, getData());
}

Kernels::Kernels() {
}

Kernels::Kernels(const Kernels& kernel)
        : height(kernel.height)
        , width(kernel.width)
        , data(std::make_unique<double []>(height * width))
{
    std::copy(kernel.data.get(), kernel.data.get() + width * height, data.get());
}

Kernels& Kernels::operator=(const Kernels& kernel) {
    if(this != &kernel) {
        height = kernel.height;
        width = kernel.width;
        data = std::make_unique<double []>(height * width);
        std::copy(kernel.data.get(), kernel.data.get() + width * height, data.get());
    }
    return *this;
}

std::pair<Kernels, Kernels> Kernels::gaussian(float sigma) {
    auto size = 2 * (int)(sigma * 3) + 1;
    auto gaussian = gaussian1d(sigma, size);

    return std::pair<Kernels, Kernels>(
            gaussian,
            gaussian.transpose());
}

std::pair<Kernels, Kernels> Kernels::gaussian(float sigma, int size) {
    auto gaussian = gaussian1d(sigma, size);

    return std::pair<Kernels, Kernels>(
            gaussian,
            gaussian.transpose());
}

Kernels Kernels::transpose() {
    Kernels transposed(width, height);
    auto* data = transposed.getData();

    for (auto i = 0; i < width; i++) {
        for (auto j = 0; j< height; j++) {
            data[j * width + i] = this->data[i * height + j];
        }
    }

    return transposed;
}

double* Kernels::getData() {
    return data.get();
}

double Kernels::getData(int x, int y) {
    return data[x * width + y];
}

Kernels Kernels::gaussian1d(float sigma, int size) {
    assert(sigma > 0);

    auto sum = 0.f;
    auto halfSize = size / 2;
    double div = std::sqrt(2 * M_PI) * sigma;

    Kernels gaussian(1, size);
    auto* data = gaussian.getData();

    for (auto i = 0; i < size; i++) {
        auto ri = i - halfSize;
        auto val = std::exp(-ri * ri / (2 * sigma * sigma)) / div;

        sum += val;
        std::cout << val << std::endl;
        data[i] = val;
    }

    std::cout << "sum: " << sum << std::endl;

    std::for_each(data, data + size, [sum](double &elem) {
        elem /= sum;
    });

    return gaussian;
}

int Kernels::getWidth()
{
    return width;
}

int Kernels::getHeight()
{
    return height;
}

std::pair<Kernels, Kernels> Kernels::sobelX() {
    return std::pair<Kernels, Kernels>(
            Kernels(1, 3, new double[3]{1, 0, -1}),
            Kernels(3, 1, new double[3]{1, 2, 1}));
}

std::pair<Kernels, Kernels> Kernels::sobelY() {
    return std::pair<Kernels, Kernels>(
            Kernels(1, 3, new double[3]{1, 2, 1}),
            Kernels(3, 1, new double[3]{1, 0, -1}));
}
