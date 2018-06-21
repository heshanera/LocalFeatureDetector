/* 
 * File:   FeatureMatcher.hpp
 * Author: heshan
 *
 * Created on June 18, 2018, 12:16 AM
 */

#ifndef FEATUREMATCHER_HPP
#define FEATUREMATCHER_HPP

#include <iostream>
#include <fstream>
#include "opencv2/opencv.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"

class FeatureMatcher {
public:
    FeatureMatcher();
    FeatureMatcher(const FeatureMatcher& orig);
    virtual ~FeatureMatcher();
    
    int match();
    
private:

};

#endif /* FEATUREMATCHER_HPP */

