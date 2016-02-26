#ifndef HOUGHDETECTOR_H
#define HOUGHDETECTOR_H

#include <iostream>
#include <QObject>
#include <opencv2/opencv.hpp>

#define LIDAR_DETECTION_X 8000
#define LIDAR_DETECTION_Y 4000
#define PI 3.14159265


typedef struct cabbageWall
{
    double a;
    double b;
}cabbageWall;



class HoughDetector
{

public:
    HoughDetector();

    void buildCartesianMap(std::vector<quint16> &distance, int factor);
    void transform();
    void getDetectedLines(std::vector<std::pair<float> > &lines);

private:
    std::vector<cv::Vec2f> detectedLines;
    std::vector<cabbageWall> walls;
    int factor;
    cv::Mat map;
    cv::Mat edges;
};

#endif // HOUGHDETECTOR_H
