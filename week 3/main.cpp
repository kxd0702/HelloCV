#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;
string detectLightColor(Mat &frame) {
    Mat hsv;
    cvtColor(frame, hsv, COLOR_BGR2HSV);
    Scalar red_low1(0, 100, 50), red_high1(10, 255, 255);
    Scalar red_low2(170, 100, 50), red_high2(180, 255, 255);
    Mat red_mask1, red_mask2, red_mask;
    inRange(hsv, red_low1, red_high1, red_mask1);
    inRange(hsv, red_low2, red_high2, red_mask2);
    red_mask = red_mask1 | red_mask2;
    Scalar green_low(35, 120, 70), green_high(90, 255, 255);
    Mat green_mask;
    inRange(hsv, green_low, green_high, green_mask);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    erode(green_mask, green_mask, kernel); 
    dilate(green_mask, green_mask, kernel);
    int red_pixels = countNonZero(red_mask);
    int green_pixels = countNonZero(green_mask);
    if (red_pixels > green_pixels && red_pixels > 10000) {
        vector<vector<Point>> contours;
        findContours(red_mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        for (auto &cnt : contours) {
            if (contourArea(cnt) > 5000) {
                Rect rect = boundingRect(cnt);
                rectangle(frame, rect, Scalar(0, 0, 255), 2);
            }
        }
        return "Red";
    } else if (green_pixels > red_pixels && green_pixels > 10000) {
        vector<vector<Point>> contours;
        findContours(green_mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        for (auto &cnt : contours) {
            if (contourArea(cnt) > 5000) {
                Rect rect = boundingRect(cnt);
                rectangle(frame, rect, Scalar(0, 255, 0), 2);
            }
        }
        return "Green";
    }
}
int main() {
    VideoCapture cap("TrafficLight.mp4");
    int frame_width = static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH));
    int frame_height = static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT));
    double fps = cap.get(CAP_PROP_FPS);
    VideoWriter out("result.avi", VideoWriter::fourcc('M','J','P','G'), fps, Size(frame_width, frame_height));
    Mat frame;
    while (cap.read(frame)) {
        string light_color = detectLightColor(frame);
        putText(frame, light_color, Point(20, 50), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(255, 255, 255), 2);
        out.write(frame);
        imshow("Traffic Light Detection", frame);
        if (waitKey(30) == 27) break;
    }
    cap.release();
    out.release();
    return 0;
}
