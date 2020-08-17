#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "detection.h"

using std::cout;
using std::endl;
using namespace Safety;

int main() {
    Detection detector;
    detector.runDetection();    
}

