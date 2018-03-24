//
// Created by vadim on 06.12.17.
//
#include <iostream>
#include "Filters.h"
#include "Image.h"
#include "Kernels.h"


Image Filters::gaussian(Image& src, float sigma, BorderTypes border) {
    Kernels kernels;
    auto gaussian = kernels.gaussian(sigma);
    Image img1 = convolve(src, gaussian.first, border);
//    img1.saveToFile("/home/vadim/CLionProjects/ComputerVision/e46_3_1.jpg");
    return convolve(img1, gaussian.second, border);
}

Image Filters::sobel(Image& src, BorderTypes border, int type) {
    auto images = sobel(src, border);
    return magnitude(images.first, images.second);
}

std::pair<Image, Image> Filters::sobel(Image &src, BorderTypes border) {
    Kernels kernels;
    auto kernelX = kernels.sobelX();
    auto kernelY = kernels.sobelY();
    return std::pair<Image, Image>(
            convolve(convolve(src, kernelX.first, border), kernelX.second, border),
            convolve(convolve(src, kernelY.first, border), kernelY.second, border));
}

Image Filters::magnitude(Image &dx, Image &dy) {
    Image dst(dx.getHeight(), dx.getWidht());

    auto* data = dst.dataPoint();
    auto* xData = dx.dataPoint();
    auto* yData = dy.dataPoint();

    for(auto i = 0, size = dst.imageSize(); i < size; i++) {
        data[i] = magnitudeVal(xData[i], yData[i]);
    }

    return dst;
}

double Filters::magnitudeVal(double dx, double dy) {
    return std::hypot(dx, dy);
}

/**
 * Свертка изображения
 * @param src
 * @param kernel
 * @param border
 * @return
 */
Image Filters::convolve(Image src, Kernels& kernel, BorderTypes border) {

    auto cPosX = kernel.getWidth() / 2, cPosY = kernel.getHeight() / 2;
    src.setBorder(border);
    Image tmp(src.getHeight(), src.getWidht());

    for (auto cI = 0, cEnd = src.getHeight(); cI < cEnd; cI++) {
        for (auto rI = 0, rEnd = src.getWidht(); rI < rEnd; rI++) {
            auto val = 0.f;

            for(auto kC = 0, kCEnd = kernel.getHeight(); kC < kCEnd; kC++) {
                for (auto kR = 0, kREnd = kernel.getWidth(); kR < kREnd; kR++) {
                    auto r = rI + kR - cPosX,
                            c = cI + kC - cPosY;
                    auto kern = kernel.getData(kC, kR);
                    auto point = src.getData(r, c);
//                    val += kernel.getData(kC, kR) * src.getData(r, c);
                    val += kern * point;
                }
            }
            tmp.setData(val, rI, cI);
        }
    }

    return tmp;
}
