#include "detection.h" 
#include <iostream>

using namespace Safety;
using namespace std;

string Detection::getDistance(cv::Rect roi, cv::Mat frame) {
    int x = roi.x;
    int y = roi.y;
    int w = roi.width;
    int h = roi.height;
    return "";
}

void Detection::runDetection() {
    //initialize classifiers and capture
    cv::CascadeClassifier bus_classifier = cv::CascadeClassifier("../Classifiers/bus.xml");
    cv::CascadeClassifier car_classifier = cv::CascadeClassifier("../Classifiers/car.xml");
    cv::CascadeClassifier bike_classifier = cv::CascadeClassifier("../Classifiers/bike.xml");
    cv::CascadeClassifier person_classifier = cv::CascadeClassifier("../Classifiers/person.xml");
    cv::VideoCapture capture(0);
    if  (!capture.isOpened()){
        cout << "Capture is not initialized" << endl;
    }

    //Real time object detection and classifications
    while (capture.isOpened()) {
        //Get frame and grayscale frames
        cv::Mat frame;
        capture >> frame;

        //get bounding boxes
        std::vector<cv::Rect>  , car_boxes, bike_boxes, person_boxes;
        bus_classifier.detectMultiScale(frame,bus_boxes, 1.3, 5);  
        car_classifier.detectMultiScale(frame, car_boxes,1.3,5);
        bike_classifier.detectMultiScale(frame,bike_boxes, 1.3, 5);  
        person_classifier.detectMultiScale(frame, person_boxes,1.3,5);

        //unpack values from each bus bounding box and draw bounding box and get distance
        for (cv::Rect bus: bus_boxes) {
            cv::Point topLeft(bus.x,bus.y);
            cv::Point bottomRight(bus.x + bus.width, bus.y + bus.height);
            cv::rectangle(frame, topLeft, bottomRight, (127,0,255), 2);
            string text = "Bus (" + getDistance(bus, frame) + "m)";
        }

        //unpack values from each car bounding box and draw bounding box and get distance
        for (cv::Rect car: car_boxes) {
            cv::Point topLeft(car.x,car.y);
            cv::Point bottomRight(car.x + car.width, car.y + car.height);
            cv::rectangle(frame, topLeft, bottomRight, (127,0,255), 2);
            string text = "Car (" + getDistance(car, frame) + "m)";
        }

        //unpack values from each bike bounding box and draw bounding box and get distance
        for (cv::Rect bike: bike_boxes) {
            cv::Point topLeft(bike.x,bike.y);
            cv::Point bottomRight(bike.x + bike.width, bike.y + bike.height);
            cv::rectangle(frame, topLeft, bottomRight, (127,0,255), 2);
            string text = "Bike (" + getDistance(bike, frame) + "m)";
        }

        //unpack values from each bus bounding box and draw bounding box and get distance
        for (cv::Rect person: person_boxes) {
            cv::Point topLeft(person.x, person.y);
            cv::Point bottomRight(person.x + person.width, person.y + person.height);
            cv::rectangle(frame, topLeft, bottomRight, (127,0,255), 2);
            string text = "Person (" + getDistance(person, frame) + "m)";
        }

        //display frameed frame with bounding box and classification text
        cv::imshow("Frame", frame);

        //break when "enter" or "return" key is pressed
        if (cv::waitKey(1) == 13) {
            break;
        }
    }

    //delete, release, and destroy
    capture.release();
    cv::destroyAllWindows();
}