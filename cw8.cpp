#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

    bool filpStatus = false;
    bool capturing = true;
    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        cerr << "error while opening" << endl;
        return -1;
    }

    int loRange[3] = { 25, 93, 65 };
    int hiRange[3] = { 82, 255, 255 };

    namedWindow("Range", WINDOW_AUTOSIZE);
    createTrackbar("loRange0", "Range", &(loRange[0]), 255);
    createTrackbar("loRange1", "Range", &(loRange[1]), 255);
    createTrackbar("loRange2", "Range", &(loRange[2]), 255);
    createTrackbar("hiRange0", "Range", &(hiRange[0]), 255);
    createTrackbar("hiRange1", "Range", &(hiRange[1]), 255);
    createTrackbar("hiRange2", "Range", &(hiRange[2]), 255);

    while (waitKey(1) != 'q')
    {

        int dilation_size = 20;
        auto structElem = getStructuringElement(MORPH_ELLIPSE, Size(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size));

        Mat frame, frameMask, frameNegMask, frameWithMask, backgroundScaledWithMask, meinniceplace;

        cap >> frame;

        cvtColor(frame, frameMask, COLOR_BGR2HSV);
        inRange(frameMask, Scalar(loRange[0], loRange[1], loRange[2]),Scalar(hiRange[0], hiRange[1], hiRange[2]), frameNegMask);

        imshow("dilate", frameNegMask);

        vector<vector<Point>> contours;
        findContours(frameNegMask, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

        // sort konturów
        sort(contours.begin(), contours.end(), [](auto& a, auto& b)
            { return contourArea(a, false) > contourArea(b, false); });
        // kontury
        for (int i = 0; i < contours.size(); i++)
        {
            approxPolyDP(contours.at(i), contours.at(i), 5, true);
        }
        Point avg[3] = {};
        double currentArea = 0;
        for (int i = 0; i < contours.size(); i++)
        {
            if (i <= 1)
            {
                Rect r = boundingRect(contours.at(i));
                int area = contourArea(contours[i], true);
                avg[i].x = r.x + r.width / 2;
                avg[i].y = r.y + r.height / 2;
                putText(frame, to_string(avg[i].y), avg[i], FONT_HERSHEY_PLAIN, 2, { 0, 0, 255, 255 });
                currentArea += contourArea(contours.at(i), false);
            }
            else
                break;
        }
        if (abs(avg[0].y - avg[1].y) < 20) {
            arrowedLine(frame, avg[0], avg[1], Scalar(0, 255, 0), 3);
            arrowedLine(frame, avg[1], avg[0], Scalar(240, 700), 3);
        }
        

        imshow("contours", frame);
    }
    return 0;
}