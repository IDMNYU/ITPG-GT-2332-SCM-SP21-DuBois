#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255, 255, 255);
    ofSetColor(0, 0, 0);
    ofSetBackgroundAuto(false);
}


//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawEllipse(ofGetMouseX(), ofGetMouseY(), 50, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    int r = ofRandom(255);
    int g = ofRandom(255);
    int b = ofRandom(255);
    ofSetColor(r, g, b);
}
