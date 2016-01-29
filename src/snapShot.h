//
//  snapShot.h
//  glitchFace
//
//  Created by shuto on 2016/01/20.
//
//
#pragma once

#include "ofApp.h"
#include <time.h>
#include <locale.h>
#include <stdlib.h>

#define ARR_LEN(array) (sizeof(array) / sizeof(array[0]))

#define QTY_SNAP 10


class snapShot{
    bool take;
    int takeCount;
    
public:
    snapShot(){
        take = false;
        takeCount = 0;
    }
    void takeSnapShot(){
        take = true;
    }
    void update(Detect detects[5]){
        if (!take) return;
        for (int i=0; i< sizeof(detects); i++) {
            if (detects[i].isDetected) {
                ofImage ss;
                ss.grabScreen(0, 0, 640, 480);
                std::ostringstream oss;
                time_t      timep;
                struct tm   *time_inf;
                char        buff[100];
                timep = time(NULL);
                time_inf = localtime(&timep);
                //strftime(buff, sizeof(buff), '%Y%m%d%H%M%S', time_inf);
                oss << "snapShot_" << buff << "" << takeCount << ".jpg";
                std::string fileName = oss.str();
                cout << "Saved snapShot named " << fileName << "." << endl;
                ss.save(fileName, OF_IMAGE_QUALITY_BEST);
                takeCount++;
                if (takeCount >= QTY_SNAP) {
                    takeCount = 0;
                    take = false;
                }
                break;
            }
        }
    }
};