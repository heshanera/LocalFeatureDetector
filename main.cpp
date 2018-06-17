/* 
 * File:   main.cpp
 * Author: heshan
 *
 * Created on June 17, 2018, 2:43 PM
 */

#include <iostream>
#include <fstream>
#include "opencv2/opencv.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"


#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

int openImg() {

    return 0;
}

int main( int argc, char** argv ) {
  
    
    std::string fileName1 = "0001.jpg", fileName2 = "0199.jpg";;
    cv::Mat img_1, img_2;
    
    // reading image 1
    img_1 = cv::imread(("trackers/Fish/img/"+fileName1), CV_LOAD_IMAGE_COLOR);
    if(! img_1.data ) {
        std::cout<<"input file Error!"<<std::endl;
        return -1;
    }
    
    // crop the image
    cv::Rect rect = cv::Rect(134,55,60,88);
    cv::Mat image1_crop = img_1(rect);
    
    // Draw a rectangle on image
    cv::Point pt1 =  cv::Point(134,55);
    cv::Point pt2 =  cv::Point((134+60),(55+88));
    cv::rectangle(img_1, pt1, pt2, cv::Scalar(255, 255, 255), 1, 8, 0);
    
    // reading image 2
    img_2 = cv::imread(("trackers/Fish/img/"+fileName2), CV_LOAD_IMAGE_COLOR);
    if(! img_2.data ) {
        std::cout<<"input file Error!"<<std::endl;
        return -1;
    }
    
    // Detect the keypoints using SURF Detector
    int minHessian = 400;
    cv::Ptr<cv::xfeatures2d::SURF> detector = cv::xfeatures2d::SURF::create( minHessian );
    std::vector<cv::KeyPoint> keypoints[2];
    
    cv::Mat imgs[] = {img_1, img_2};
    std::ofstream outFile;
    std::string outFileName[] = {"features0001.csv","features0199.csv"};
    
    for (int i = 0; i < 2; i++) {
        detector->detect( imgs[i], keypoints[i] );
        outFile.open (outFileName[i]);
        outFile<<"pointX,pointY,size,angle,response,octave,classId\n";
        for (int j = 0; j < keypoints[i].size(); j++) {
            outFile<<(float)keypoints[i].at(j).pt.x<<',';
            outFile<<(float)keypoints[i].at(j).pt.y<<',';
            outFile<<(float)keypoints[i].at(j).size<<',';
            outFile<<(float)keypoints[i].at(j).angle<<',';
            outFile<<(float)keypoints[i].at(j).response<<',';
            outFile<<(float)keypoints[i].at(j).octave<<',';
            outFile<<(float)keypoints[i].at(j).class_id<<'\n';
        }
        outFile.close();
    }
    
    // extractor
    cv::Ptr<cv::xfeatures2d::SURF> extractor = cv::xfeatures2d::SURF::create();
    cv::Mat descriptors_1, descriptors_2;
    extractor->detect(img_1, keypoints[0], descriptors_1);
    extractor->detect(img_2, keypoints[1], descriptors_2);
    
    cv::BFMatcher matcher(cv::NORM_L2);
    std::vector< cv::DMatch > matches;
    matcher.match(descriptors_1, descriptors_2, matches);
    
    // draw matches
    cv::Mat img_matches;
    drawMatches( img_1, keypoints[0], image1_crop, keypoints[1], matches, img_matches );
    
    // displaying the images
//    cv::imshow( fileName1, img_1 ); // image 1
//    cv::imshow( fileName2, img_2 ); // image 2
//    cv::imshow("image1_crop", image1_crop); // cropped image 1
    imshow("Matches", img_matches );
    
    cv::waitKey(0);  
    
    return 0;
    
}

