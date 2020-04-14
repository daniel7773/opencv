// Компьютерные Технологии в Видеопроизводстве, письмо 8 апреля

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat img1 = imread("apples.png");
    Mat dst;

    std::vector<cv::Mat> rgb_vec;
    // cv::split(img1, rgb_vec);
    //  cv::cvtColor(img1, img1, CV_BGR2Lab);
    //  Mat one = rgb_vec[0];
    //  Mat two = rgb_vec[1];
    // Mat three = rgb_vec[2];
    //   imshow("B", one);
    //  imshow("G", two);
    // imshow("R", three);

    Mat hsv;
    cvtColor(img1, hsv, COLOR_BGR2HSV);

    Mat mask1, mask2;

    inRange(hsv, Scalar(0, 120, 70), Scalar(10, 255, 255), mask1);

    inRange(hsv, Scalar(170, 120, 70), Scalar(180, 255, 255), mask2);

    mask1 = mask1 + mask2;

    for (int y = 0; y < mask1.rows; y++)
        for (int x = 0; x < mask1.cols; x++) {
               if (mask1.at<Vec3b>(Point(x, y))[1] <80 || mask1.at<Vec3b>(Point(x, y))[0] > 210) {
                mask1.at<Vec3b>(Point(x, y))[1] = 155;
            }
        }

    Mat mask_floodfill = mask1.clone();
    Mat mask;

    floodFill(mask_floodfill, cv::Point(0, 0), Scalar(255));

    bitwise_not(mask_floodfill, mask2);

    mask = (mask2 | mask);

    // dilate(mask, mask, Mat(), Point(-1, -1), 3, 1, 1); // сомнительно

    Mat out(img1.size(), img1.type());
    out = Scalar::all(255);
    //Копируем зашумленное изображение через маску
    img1.copyTo(out, mask);

    cv::inRange(img1, cv::Scalar(0, 0, 0), cv::Scalar(200, 200, 200), dst);


    imshow("output", out);
     imshow("input", img1);
      imshow("mask1", mask1);
     
    waitKey();
    return 0;
}
