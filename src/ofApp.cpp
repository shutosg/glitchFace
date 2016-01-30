#include "ofApp.h"
#include <sstream>

//--------------------------------------------------------------
void ofApp::setup(){
    finder.setup("haarcascade_frontalface_default.xml");  // 顔検出器
    finder.setScaleHaar(2.0);
    
    ofSetFrameRate(30);
    quality = OF_IMAGE_QUALITY_WORST;
    
    grabber.initGrabber(640, 480, true);
    video.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    
    for (int i=0; i<QTY_DETECT; i++) {
        detects[i] = new Detect();  // 検出した顔を管理するオブジェクト
    }
    
    snapshot = *new snapShot();  // スクリーンショット用オブジェクト
    
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();  // ビデオをアップデート
    
    ofPushMatrix();  // 鏡面処理
    ofScale(-1, 1);
    grabber.draw(-ofGetWidth(), 0, ofGetWidth(), ofGetHeight());
    ofPopMatrix();
    
    video.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    
    finder.findHaarObjects(video);  // 画面を顔検出器に投げる
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    video.draw(0, 0);
    
    for(unsigned int i = 0; i < finder.blobs.size(); i++) {
        ofRectangle cur = finder.blobs[i].boundingRect;
        float curx, cury, curw, curh;
        curw = cur.width;
        curh = cur.height;
        curx = cur.x - curw * 0.2;  // 顔領域を少し拡大する処理
        cury = cur.y - curh * 0.2;
        curw *= 1.4;
        curh *= 1.4;
        
        ofxCvColorImage rect;
        rect.setFromPixels(video.getPixels(), 640, 480);
        rect.setROI(curx, cury, curw, curh);
        ofImage writeImg;
        writeImg.setFromPixels(rect.getRoiPixels());
        std::ostringstream oss;
        oss << "faces_" << i << ".jpg";
        std::string fileName = oss.str();
        writeImg.save(fileName, quality);  // 顔領域を悪い品質のJPEGとして保存
        
        ofDrawRectangle(cur.x, cur.y, cur.width, cur.height);
        ofBuffer file = ofBufferFromFile(fileName);
        int fileSize = file.size();
        char *buffer = file.getBinaryBuffer();  // 保存したJPEGをバッファーに読込み
        
        for(unsigned int j=0; j<5; j++) {
            int whichByte = (int) ofRandom(fileSize);  // ビットを立てるバイト位置をランダムに決定
            int whichBit = ofRandom(8);  // ランダムに立てるビットを設定
            char bitMask = 1 << whichBit;
            buffer[whichByte] |= bitMask;  // glitch
        }
        
        ofBufferToFile(fileName, file);  // glitchしたファイルを保存
        detects[i]->set(curx, cury, curw, curh);
        
    }
    
    
    // 再度読込みして顔に貼り付け
    for(unsigned int i = 0; i < QTY_DETECT; i++) {
        cout << i << "'s ";
        detects[i]->check();
        if (!detects[i]->isDetected) continue;
        ofImage loadImg;
        std::ostringstream oss;
        oss << "faces_" << i << ".jpg";
        std::string fileName = oss.str();
        if (!loadImg.load(fileName)) break;
        loadImg.draw(detects[i]->x, detects[i]->y);
    }
    
    snapshot.update(detects);  // スクリーンショット撮影
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 32:
            snapshot.takeSnapShot();
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
//--------------------------------------------------------------
void ofApp::exit(){
    for(unsigned int i = 0; i < QTY_DETECT; i++) {
        delete detects[i];
    }
}