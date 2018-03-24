//
// Created by vadim on 27.11.2017.
//
#include <iostream>
#include <bits/unique_ptr.h>

#ifndef COMPUTERVISION_IMAGESOURCE_H
#define COMPUTERVISION_IMAGESOURCE_H

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

/**
 * Класс исходного изображения. Используется как для хренения самого изображения (ширина/высота/значения пикселей),
 * так и для манипуляции изображением, например, нормализацией, преобразованию в серые тона
 */
class ImageSource {

private:
//    double **data;
    std::unique_ptr<double[]> data;
    int height;
    int width;
//    char borderType = 'z';
    int borderMode;

public:
//    const int TYPE_BORDER_WITHOUT = 1;
//    const int TYPE_BORDER_BLACK = 2;
//    const int TYPE_BORDER_WRAPPING = 3;
//    const int TYPE_BORDER_MIRROR = 4;

public:
    void setData(double d, unsigned int x, unsigned int y);

    double getData(int x, int y);

    int getHeight() const;

    int getWidth() const;

    void setBorderMode(char border);

//    unique_ptr<ImageSource> copy() const;

    ImageSource(int height, int width);

//    ImageSource();

    void saveToFile(std::string filename);

//    void normalize();

};


#endif //COMPUTERVISION_IMAGESOURCE_H
