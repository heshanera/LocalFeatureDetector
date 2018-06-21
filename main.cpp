/* 
 * File:   main.cpp
 * Author: heshan
 *
 * Created on June 17, 2018, 2:43 PM
 */

#include "FeatureMatcher.hpp"
#include "EdgeDetector.hpp"


int main( ) {
    
    FeatureMatcher fm;
    fm.match();
    
    EdgeDetector ed;
    ed.detect();
    
}

