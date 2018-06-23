/* 
 * File:   FeatureMatcher.cpp
 * Author: heshan
 * 
 * Created on June 18, 2018, 12:16 AM
 */

#include "FeatureMatcher.hpp"

FeatureMatcher::FeatureMatcher() { }

int FeatureMatcher::match() {

    // reading images
    cv::Mat img_1 = cv::imread("data/Fish/img/0001.jpg", CV_LOAD_IMAGE_UNCHANGED);
    cv::Mat img_2 = cv::imread("data/Fish/img/0199.jpg", CV_LOAD_IMAGE_UNCHANGED);
    if(!img_1.data || !img_2.data) {
        std::cout<<"input files Error!"<<std::endl;
        return -1;
    }
    
    // crop the image
    cv::Rect rect = cv::Rect(134,55,60,88);
    cv::Mat image1_crop;
    img_1(rect).copyTo(image1_crop);
    
    // Draw a rectangle on image
    cv::Point pt1 =  cv::Point(134,55);
    cv::Point pt2 =  cv::Point((134+60),(55+88));
    cv::rectangle(img_1, pt1, pt2, cv::Scalar(255, 255, 255), 1, 8, 0);
    
    // SURF feature detector
    int minHessian = 400;
    cv::Ptr<cv::xfeatures2d::SURF> detector = cv::xfeatures2d::SURF::create();
    detector->setHessianThreshold(minHessian);
    std::vector<cv::KeyPoint> keypoints[3];
    
    detector->detect(img_1,keypoints[0],cv::Mat());
    detector->detect(img_2,keypoints[1],cv::Mat());
    detector->detect(image1_crop,keypoints[2],cv::Mat());
    
    // Writing to keypoints to CSV
    std::ofstream outFile;
    std::string outFileName[] = {"features0001.csv","features0199.csv"};
    
    for (int i = 0; i < 2; i++) {
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
    
    // Computing the keypoints
    cv::Mat descriptors_1, descriptors_2;
    detector->compute(img_1,keypoints[0],descriptors_1);
    detector->compute(image1_crop,keypoints[2],descriptors_2);
    
    // Brute Force Matcher
    cv::BFMatcher matcher(cv::NORM_L2,true);
    std::vector< cv::DMatch > matches;
    matcher.match(descriptors_1, descriptors_2, matches);
    
    // draw brute force matches
    cv::Mat img_matches;
    drawMatches( img_1, keypoints[0], image1_crop, keypoints[2], matches, img_matches);
    cv::imwrite("output/output_matching.jpg", img_matches);
    
    // FLANN Matcher
    cv::FlannBasedMatcher matcher2;
    std::vector< cv::DMatch > matches2;
    matcher2.match( descriptors_1, descriptors_2, matches2 );
    
    double max_dist = 0; double min_dist = 100;
    
    //-- Quick calculation of max and min distances between keypoints
    for( int i = 0; i < descriptors_1.rows; i++ ) { 
        double dist = matches2[i].distance;
        if( dist < min_dist ) min_dist = dist;
        if( dist > max_dist ) max_dist = dist;
    }
    
    std::vector< cv::DMatch > good_matches;
    for( int i = 0; i < descriptors_1.rows; i++ ) { 
        if( matches2[i].distance <= std::max(3*min_dist, 0.02) ) { 
            good_matches.push_back( matches2[i]); 
        }
    }
    
    // draw FLANN matches
    cv::Mat img_matches2;
    drawMatches( img_1, keypoints[0], image1_crop, keypoints[2], good_matches, img_matches2);
    cv::imwrite("output/output_FLANN_matching.jpg", img_matches2);
    
    
    // displaying the images
    cv::imshow("Image 1", img_1); // image 1
    cv::imshow("Image 2", img_2); // image 2
    imshow("Brute Force Matches", img_matches );
    imshow("FLANN Matches", img_matches2 );
    
    cv::waitKey(0);  
    
    return 0;
    
}


