/* 
 * File:   main.cpp
 * Author: heshan
 *
 * Created on June 17, 2018, 2:43 PM
 */

#include <iostream>
#include "opencv2/opencv.hpp"
 
int main( int argc, char** argv )
{
  std::cout << "OpenCV version : " << CV_VERSION << std::endl;
  std::cout << "Major version : " << CV_MAJOR_VERSION << std::endl;
  std::cout << "Minor version : " << CV_MINOR_VERSION << std::endl;
  std::cout << "Subminor version : " << CV_SUBMINOR_VERSION << std::endl;
 
  if ( CV_MAJOR_VERSION < 3)
  {
      // Old OpenCV 2 code goes here. 
  } else
  {
      // New OpenCV 3 code goes here. 
  }
}

