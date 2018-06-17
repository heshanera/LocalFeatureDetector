/* 
 * File:   EdgeDetector.hpp
 * Author: heshan
 *
 * Created on June 18, 2018, 12:14 AM
 */

#ifndef EDGEDETECTOR_HPP
#define EDGEDETECTOR_HPP

class EdgeDetector {
public:
    EdgeDetector();
    EdgeDetector(const EdgeDetector& orig);
    virtual ~EdgeDetector();
    
    int detect();
    
private:

};

#endif /* EDGEDETECTOR_HPP */

