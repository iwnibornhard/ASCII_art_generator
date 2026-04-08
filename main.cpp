#include <iostream>
#include <random>
#include <string>
#include "opencv2/opencv.hpp"

int main() {
    //set of ASCII chars
    //ASCII chars going from densest (dark areas) to lower density (light ares)
    std::string chars {"$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'."};

    //defining a variable that will contain stock image
    cv::Mat imgOrg;

    //asking user what logo they want to convert to ASCII
    int choiceImage;
    std::cout << "Choose what image to convert to ASCII:\n\t1.Apple logo\n\t2.Linux logo\n\t3.Windows logo\n";
    std::cin >> choiceImage;
    switch (choiceImage) {
        case 1: {
            //opening apple logo
            imgOrg = cv::imread("../images/apple.png", cv::IMREAD_UNCHANGED);
            break;
        }
        case 2: {
            //opening linux logo
            imgOrg = cv::imread("../images/linux.png", cv::IMREAD_UNCHANGED);
            break;
        }
        case 3: {
            //opening windows logo
            imgOrg = cv::imread("../images/win.png", cv::IMREAD_UNCHANGED);
            break;
        }
        default: {
        std::cout << "Incorrect option.";
        return -1;
        }
    }

    //Showing user a picture they select
    cv::resize(imgOrg, imgOrg, cv::Size(250, 250));
    cv::namedWindow("original image");
    cv::imshow("original image", imgOrg);
    //displays image in the front tab
    cv::setWindowProperty("original image", cv::WND_PROP_TOPMOST, 1);
    cv::waitKey(0);
    cv::destroyAllWindows();

    //width and height of our image
    //NOTE: if output is terminal - then height = width / 2.
    int width, height;


    //checking if image was opened.
    if (imgOrg.empty())
    {
        std::cout <<"Image was not found.";
        return -1;
    }

    //asking user for their preferred output
    int choiceOutput;
    std::cout << "Select image output:\n\t1.Terminal\n\t2.Window\n";
    std::cin >> choiceOutput;
    switch (choiceOutput) {
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
            cv::resize(imgGray, imgResult, cv::Size(width, width/3));

            // resizing original image
            //it will be used later for alpha channel check (transparency)
            cv::resize(imgOrg, imgOrg, cv::Size(width, width/3));

            // \t is used for more solid output
            std::cout << "\t";
            for (int i {0}; i < imgResult.rows; i++) {
                //pointer to the start of each row
                uchar* rowPtr = imgResult.ptr<uchar>(i);
                for (int j {0}; j < imgResult.cols; j++) {
                    //j pixel of i row
                    uchar pixel = rowPtr[j];
                    //calculating which char to use
                    uchar index = (static_cast<double>(pixel) / 255.0) * (chars.length() - 1);
                    //checking if pixel if transparent in image containing Alpha channel
                    uchar alpha = imgOrg.ptr<uchar>(i)[j*4+3];
                    if (alpha < 128) {
                        //if pixel is transparent - skip the output
                        std::cout << " ";
                    } else {
                        std::cout << chars[index];
                    }
                }
                std::cout << "\n\t";
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