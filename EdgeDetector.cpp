/* 
 * File:   EdgeDetector.cpp
 * Author: heshan
 * 
 * Created on June 18, 2018, 12:14 AM
 */

#include "EdgeDetector.hpp"

EdgeDetector::EdgeDetector() { }

int EdgeDetector::detect() {
    
    cv::Mat img;
    cv::Mat detected_edges;
    int lowThreshold = 100;
    int highThreshold = 200;
    int kernel_size = 3;
    
    std::string inFiles[] = {"0001.jpg", "0199.jpg"};
    std::string outFiles[] = {"output/output3.jpg", "output/output4.jpg"};
    
    for (int i = 0; i < 2; i++) {
        img = cv::imread( ("data/Fish/img/"+inFiles[i]), CV_LOAD_IMAGE_GRAYSCALE);
        if( img.empty() ) return -1; 
        cv::blur( img, detected_edges, cv::Size(3,3) );
        cv::Canny( img, detected_edges, lowThreshold, highThreshold, kernel_size );
        cv::imwrite(outFiles[i], detected_edges);
    }
    return 0;
}
