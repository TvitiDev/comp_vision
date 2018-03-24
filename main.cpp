#include <iostream>
#include "Image.h"
#include "ImageSource.h"
#include "Filters.h"

void lab1();

void lab1() {
    Image img = Image("../picture/e46.jpg");
    img.saveToFile("../picture/e46_1.jpg");

    Image img2 = img.normalize(img);
    img2.saveToFile("../picture/e46_2.jpg");

    Filters filters;

    Image img3 = filters.gaussian(img2, 1.8f, BorderTypes::TYPE_BORDER_WITHOUT);
    img3.saveToFile("../picture/e46_3_2.jpg");

    Image img4 = filters.sobel(img3, BorderTypes::TYPE_BORDER_WITHOUT, 1);
    img4.saveToFile("../picture/e46_4.jpg");

}


int main() {

    lab1();

    return 0;
}