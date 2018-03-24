//
// Created by vadim on 27.11.2017.
//

#include <algorithm>
#include "ImageSource.h"

ImageSource::ImageSource(int height, int width)
{
    this->height = height;
    this->width = width;
//    borderMode = BorderTypes::TYPE_BORDER_BLACK;
//    data = double[] (this->height * this->width);
    std::unique_ptr<double[]> data(new double[this->height * this->width]);
}

void ImageSource::setData(double value, unsigned int x, unsigned int y)
{
    data[x * height + y] = value;
}

/**
 * Установка режима обрабоки краевых значений
 * @param borderMode
 */
void ImageSource::setBorderMode(char borderMode)
{
   this->borderMode = borderMode;
}

double ImageSource::getData(int x, int y) {
    if (x >= 0 && y >= 0 && x < width && y < height)
        return data[x * height + y];
    int clearY = y;
    int clearX = x;
    switch (borderMode) {
        case BorderTypes::TYPE_BORDER_MIRROR:
//        case TYPE_BORDER_WITHOUT:

//        case 'c':
//        case TYPE_BORDER_WRAPPING:
        case 1:
            if (height <= clearY)
                clearY = height - 1;

            if (0 > clearY)
                clearY = 0;

            if (width <= clearX)
                clearX = width - 1;

            if (0 > clearX)
                clearX = 0;
            break;
        case 't':
            clearX = (width + x) % width;
            clearY = (height + y) % height;
            break;
        case 's':
            if (height <= clearY)
                clearY = 2 * height - clearY;

            if (0 > clearY)
                clearY = -clearY;

            if (width <= clearX)
                clearX = 2 * width - clearX;

            if (0 > clearX)
                clearX = -clearX;
            break;
//        case TYPE_BORDER_BLACK:
        case 0:
        default:
            return 0;
    }
    return data[clearX * height + clearY];
}


int ImageSource::getHeight() const {
    return height;
}

int ImageSource::getWidth() const {
    return width;
}

//unique_ptr <ImageSource> ImageSource::copy() const {
//    unique_ptr <ImageSource> image = make_unique<ImageSource>(height, width);
//    std::copy(data.get(), data.get() + height * width, image->data.get());
//    image->setBorderMode(borderMode);
//    return image;
//}

void ImageSource::saveToFile(std::string filename) {

//    unique_ptr <Images> image = make_unique<Images>(width, height, QImage::Format_RGB32);
    cv::Mat img = cv::Mat(height, width, CV_32FC1, &data);
    cv::Mat saved;
    img.convertTo(saved, CV_8U, 255);
    cv::imwrite(filename, saved);
//    cv::Mat img = cv::imwrite(filename, );
//    for (int i = 0; i < width; i++)
//        for (int j = 0; j < height; j++) {
//            int brightness = (int) (getData(i, j) * 255);
//            image->setPixel(i, j, qRgb(brightness, brightness, brightness));
//        }
//    image->save(filename, "JPG");
}

//void ImageSource::normalize() {
//    auto data_ptr = data.get();
//    auto result = minmax_element(data_ptr, data_ptr + height * width);
//    cout << *(result.first) << " " << *(result.second) << endl;
//    double floor = *(result.second) - *(result.first);
//    for (int i = 0; i < width; i++)
//        for (int j = 0; j < height; j++) {
//            setData((getData(i, j) - *(result.first)) / floor, i, j);
//        }
//}