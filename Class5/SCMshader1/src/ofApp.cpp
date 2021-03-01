#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    theShader.load("lukeBlur"); // loads shader files ('.vert' and '.frag')
    theImage.load("img.jpg"); // image to process
    
    // allocate memory for frame buffer objects:
    theFBO.allocate(theImage.getWidth(), theImage.getHeight());
    theFBO2.allocate(theImage.getWidth(), theImage.getHeight());
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    float xf = ofMap(ofGetMouseX(), 0, ofGetWidth(), 1, 16, true);
    float yf = ofMap(ofGetMouseY(), 0, ofGetHeight(), 1, 16, true);
    
    theFBO.begin(); // initialize framebuffer
    theShader.begin(); // start shader
    theShader.setUniform1f("blurX", xf); // set parameter
    theShader.setUniform1f("blurY", yf); // set parameter

    theImage.draw(0,0); // draw image in
    theShader.end(); // close out shader
    theFBO.end(); // close out FBO
    
    ofSetColor(255, 255, 255); // 'tint' command
    theFBO.draw(0,0); // draw FBO

//    theFBO2.begin();
//    theShader.begin();
//    theShader.setUniform1f("blurX", xf);
//    theShader.setUniform1f("blurY", yf);
//
//    theFBO.draw(0,0);
//    theShader.end();
//    theFBO2.end();
//
//    ofSetColor(ofColor::white);
//    theFBO2.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
