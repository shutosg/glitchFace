//
//  detect.h
//  glitchFace
//
//  Created by shuto on 2016/01/20.
//
//
#pragma once

#include <time.h>

#ifndef detect_h
#define detect_h


#endif /* detect_h */

class Detect {
    
public:
    bool isDetected;
    float x;
    float y;
    int w;
    int h;
    clock_t time;
    const static clock_t life = 4 * CLOCKS_PER_SEC;
    
    Detect(){
        isDetected = false;
        x = 0.0;
        y = 0.0;
        w = 0;
        h = 0;
    }
    void set(float x, float y, int w, int h) {
        isDetected = true;
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        time = clock();
        return 0;
    }
    void check() {
        if (clock()-time > life) isDetected = false;
        cout << "Life is " << (life + time - clock())/CLOCKS_PER_SEC << "sec." << endl;
        return 0;
    }
    
};