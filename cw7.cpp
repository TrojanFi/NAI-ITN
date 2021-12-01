#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

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

    int width = 0;
    int high = 0;
    cout << "put width" << endl;
    cin >> width;
    cout << "put high" << endl;
    cin >> high;


    namedWindow("Range", WINDOW_AUTOSIZE);
    namedWindow("HSV4", WINDOW_AUTOSIZE);

    int LowH = 0;
    int HighH = 0;
    int LowS = 0;
    int HighS = 0;
    int LowV = 0;
    int HighV = 0;

    createTrackbar("LowH", "Range", &LowH, 180);
    createTrackbar("HighH", "Range", &HighH, 180);
    createTrackbar("LowS", "Range", &LowS, 255);
    createTrackbar("HighS", "Range", &HighS, 255);
    createTrackbar("LowV", "Range", &LowV, 255);
    createTrackbar("HighV", "Range", &HighV, 255);

    do {
        Mat frame, Range, pokazaniehsv;
        Mat dst = frame;
        char k = waitKey(1);
        if (k == 't') filpStatus = true;
        if (k == 'y') filpStatus = false;

        if (cap.read(frame)) {

            if (filpStatus) {
                flip(frame, dst, 1);
                imshow("Not-yet smart window", dst);
            }
            else
                imshow("Not-yet smart window", frame);
        }
        else {
            capturing = false;
        }
        
        if (k == 'b') {
            Mat blur, newSize;
            GaussianBlur(frame, blur, Size(5, 5), 0);
            resize(blur, newSize, { width,high });
            imshow("Blur window", newSize);
        }
        else if(k == 'n') {
            destroyWindow("Blur window");
        }

        if(k == 'x') {

            Mat blur,newSize;
            auto r = selectROI("Caught frame", frame);
            Mat roi = frame(r);
            GaussianBlur(roi, blur, Size(5, 5), 0);
            resize(blur, newSize,{ width,high });
            imshow("Blur + New Size", newSize);
            imwrite("Zapis.JPG", newSize);
        }


        cvtColor(frame, Range, COLOR_BGR2HSV);
        cvtColor(frame, pokazaniehsv, COLOR_BGR2HSV);

        inRange(Range, Scalar(LowH, LowV, LowS), Scalar(HighS, HighH, HighV), Range);

        putText(pokazaniehsv, to_string(LowH), { 10,30 }, FONT_HERSHEY_PLAIN, 1.0, { 255,255,255,8 });
        putText(pokazaniehsv, to_string(HighH), { 10,50 }, FONT_HERSHEY_PLAIN, 1.0, { 255,255,255,8 });
        putText(pokazaniehsv, to_string(LowS), { 10,70 }, FONT_HERSHEY_PLAIN, 1.0, { 255,255,255,8 });
        putText(pokazaniehsv, to_string(HighS), { 10,90 }, FONT_HERSHEY_PLAIN, 1.0, { 255,255,255,8 });
        putText(pokazaniehsv, to_string(LowV), { 10,110 }, FONT_HERSHEY_PLAIN, 1.0, { 255,255,255,8 });
        putText(pokazaniehsv, to_string(HighV), { 10,130 }, FONT_HERSHEY_PLAIN, 1.0, { 255,255,255,8 });

        imshow("Range", Range);
        imshow("HSV4", pokazaniehsv);



        if (k == 'q') {
            capturing = false;
        }
    } while (capturing);
    return 0;
}