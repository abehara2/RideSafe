#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace std;

namespace Safety {
    class Detection {
        public: 
            //Detection();
            void runDetection();
            string getDistance(cv::Rect, cv::Mat frame);
    };  
}

