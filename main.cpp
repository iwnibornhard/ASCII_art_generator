#include <iostream>
#include <random>
#include <string>
#include "opencv2/opencv.hpp"

int main() {
    //set of ASCII chars
    //ASCII chars going from densest (dark areas) to lower density (light ares)
    std::string chars {"$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'."};
    //initializing a variable that will contain our grayscaled image
    cv::Mat imgOrg {cv::imread("C:/Users/tema/CLionProjects/ASCII_art_generator/image1.jpg", cv::IMREAD_GRAYSCALE)};
    //checking if image was opened.
    if (imgOrg.empty())
    {
        std::cout <<"Image was not found.";
        return -1;
    }
    int width {50}, height {25};
    //creating a var where resized image will be stored
    cv::Mat imgResized;
    //resizing original image and putting the result into recently created variable
    //WHEN OUTPUT IS IN TERMINAL - HEIGHT = WEIDTH/2
    cv::resize(imgOrg, imgResized, cv::Size(width, height));
    cv::imshow("original image:", imgResized);
    cv::waitKey(0);
    uchar* rowPtr;
    for (int i {0}; i < imgResized.rows; i++) {
        rowPtr = imgResized.ptr<uchar>(i);
        for (int j {0}; j < imgResized.cols; j++) {
            uchar pixel = rowPtr[j];
            int index = (static_cast<double>(pixel) / 255.0) * (chars.length() - 1);
            std::cout << chars[index];
        }
        std::cout << "\n";
    }

    return 0;
}