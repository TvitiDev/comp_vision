//
// Created by vadim on 29.11.2017.
//

#include "Image.h"
#include <iostream>
#include <memory>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;

/**
 * Конструктор для загрузки изображения
 * @param filename
 */
Image::Image(string filename)
{
    // загружаем изображение извне. Используем OpenCV лишь для загрузки
    cv::Mat img = cv::imread(filename, cv::IMREAD_COLOR);
    height = img.rows;
    width = img.cols;
    data = new double[height * width];

    // преобразование в оттенки серого
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            cv::Vec3b ptr = img.at<cv::Vec3b>(i, j);
            double color = .299f * ptr[2] + .587f * ptr[1] + .114f * ptr[0];
            setData(color, j, i);
        }
    }
}

void Image::setData(double value, unsigned int x, unsigned int y)
{
    data[y * width + x] = value;
}

/**
 *
 * @param image
 * @return Image
 */
Image Image::normalize(Image sourceImage)
{
    Image normalizeImg(sourceImage.height, sourceImage.width);

    auto* normalizeData = normalizeImg.dataPoint();
    auto* sourceData = sourceImage.dataPoint();

    //find max, min values for one-channel image
    auto minmax = std::minmax_element(sourceData, sourceData + sourceImage.imageSize());
    auto min = *minmax.first;
    auto max = *minmax.second;
    auto norm  = (max - min) / 255;

    //normalize
    for(auto i = 0, size = sourceImage.imageSize(); i < size; i++) {
        normalizeData[i] = (sourceData[i] - min) / norm;
    }

    return normalizeImg;
}

/**
 * Второй конструктор. Переписать на клонирование
 * @param image
 */
Image::Image(int height, int width)
{
    this->height = height;
    this->width = width;
    data = new double[height * width];
}


double* Image::dataPoint() const
{
    return data;
}

int Image::imageSize() const
{
    return height * width;
}

int Image::getWidht()
{
    return width;
}

int Image::getWidht() const
{
    return width;
}

int Image::getHeight()
{
    return height;
}

int Image::getHeight() const
{
    return height;
}

/**
 * Сохраняем изображение в файл
 *
 * @param filename
 */
void Image::saveToFile(std::string filename) {

    auto outData = new char[width * height];
    int size = width * height;

    for (int i = 0; i < size; i++) {
        double value = data[i];
        value = value < 0 ? 0 : value;
        value = value > 255 ? 255 : value;
        outData[i] =(char) value;
    }

    cv::Mat img = cv::Mat(height, width, CV_8UC1, outData);
    cv::imwrite(filename, img);

    delete(outData);
}

/**
 * Указываем, как обрабатывать края изображения
 * @param border
 */
void Image::setBorder(int border) {
    borderMode = border;
}

/**
 * Получение точки изображения, в зависимости от типа обработки крайних значений
 * @param x
 * @param y
 * @return
 */
double Image::getData(int x, int y) {
    if (x >= 0 && y >= 0 && x < width && y < height)
        return data[y * width + x];

    int clearY = y;
    int clearX = x;
    switch (borderMode) {
        case BorderTypes::TYPE_BORDER_WITHOUT:
            if (height <= clearY)
                clearY = height - 1;

            if (0 > clearY)
                clearY = 0;

            if (width <= clearX)
                clearX = width - 1;

            if (0 > clearX) {
                clearX = 0;
            }
            break;
        case BorderTypes::TYPE_BORDER_WRAPPING:
            clearX = (width + x) % width;
            clearY = (height + y) % height;
            break;
        case BorderTypes::TYPE_BORDER_MIRROR:
            if (height <= clearY)
                clearY = 2 * height - clearY;

            if (0 > clearY)
                clearY = -clearY;

            if (width <= clearX)
                clearX = 2 * width - clearX;

            if (0 > clearX)
                clearX = -clearX;
            break;
        case BorderTypes::TYPE_BORDER_BLACK:
        default:
            return 0;
    }
    return data[clearY * width + clearX];
}
