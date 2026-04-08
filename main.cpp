#include <iostream>
#include <random>
#include <string>
#include "opencv2/opencv.hpp"

int main() {
    //set of ASCII chars
    //ASCII chars going from densest (dark areas) to lower density (light ares)
    std::string chars {"$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'."};

    //initializing a variable that will contain our image
    cv::Mat imgOrg {cv::imread("C:/Users/tema/CLionProjects/ASCII_art_generator/image1.jpg")};
    cv::imshow("original image:", imgOrg);
    cv::waitKey(0);

    //width and height of our image
    //NOTE: if output is terminal - then height = width / 2.
    int width, height;


    //checking if image was opened.
    if (imgOrg.empty())
    {
        std::cout <<"Image was not found.";
        return -1;
    }

    //asking user for their preffered output
    int choice;
    std::cout << "Select image output:\n\t1.Terminal\n\t2.Window\n";
    std::cin >> choice;
    switch (choice) {
        //terminal output
        case 1: {
            //asking user to input width
            std::cout << "Input the width of picture: \n";
            std::cin >> width;

            //creating a var where grayscale image will be stored
            cv::Mat imgGray;
            cv::cvtColor(imgOrg, imgGray, cv::COLOR_BGR2GRAY);

            //creating a var where resized image will be stored
            cv::Mat imgResult {imgGray.clone()};
            //resizing original image and putting the result into recently created variable
            //WHEN OUTPUT IS IN TERMINAL - HEIGHT = WEIDTH/2
            cv::resize(imgGray, imgResult, cv::Size(width, width/2));
            uchar* rowPtr;
            for (int i {0}; i < imgResult.rows; i++) {
                rowPtr = imgResult.ptr<uchar>(i);
                for (int j {0}; j < imgResult.cols; j++) {
                    uchar pixel = rowPtr[j];
                    int index = (static_cast<double>(pixel) / 255.0) * (chars.length() - 1);
                    std::cout << chars[index];
                }
                std::cout << "\n";
            }
            break;
        }
        //separate window output
        case 2: {
            std::cout << "Work in progress.\n";
            break;
        }
        default: {
            std::cout << "Incorrect option.";
            return -1;
        }
    }


    return 0;
}