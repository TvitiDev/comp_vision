//
// Created by vadim on 29.11.2017.
//

#ifndef COMPUTERVISION_IMAGE_H
#define COMPUTERVISION_IMAGE_H
#include <string>
//#include "ImageSource.h"

enum BorderTypes {
    TYPE_BORDER_WITHOUT = 1,
    TYPE_BORDER_BLACK = 2,
    TYPE_BORDER_WRAPPING = 3,
    TYPE_BORDER_MIRROR = 4
};

/**
 * Класс для работы с изображением
 *
 * Загрузка, сохранение....
 */
class Image {

private:
    int height;
    int width;
    int borderMode = BorderTypes::TYPE_BORDER_BLACK;
    double *data;

public:
    Image(std::string filename);

    Image(int height, int width);

    double *dataPoint() const;

    void saveToFile(std::string filename);

    void setData(double value, unsigned int x, unsigned int y);

    Image normalize(Image image);

    int imageSize() const;

    int getWidht();

    int getHeight();

    double getData(int x, int y);

    void setBorder(int border);

    int getHeight() const;

    int getWidht() const;
};


#endif //COMPUTERVISION_IMAGE_H
