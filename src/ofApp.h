#pragma once

#include "ofMain.h"
#include "ofxCvHaarFinder.h"
#include "detect.h"
#include "snapShot.h"
#define ARR_LEN(array) (sizeof(array) / sizeof(array[0]))
#define QTY_DETECT 5
#define QTY_SNAP 10

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void exit();
    
    ofImage video;
    ofImageQualityType quality;
    void reset();
    ofVideoGrabber grabber;
    //Detect detects[QTY_DETECT];
    Detect *detects[QTY_DETECT];
    
    snapShot snapshot;
    
    ofxCvHaarFinder finder;
};

