#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    ofSetColor(255, 255, 255);
    
    // configure and start the audio:
    ofSoundStreamSettings settings; // this is a data structure for audio settings
    soundStream.printDeviceList(); // what are our devices?

    // i don't think i need this:
//    ofSoundDevice soundDevice;
//    soundDevice.deviceID = 3;
//    settings.setOutDevice(soundDevice);
    
    settings.setOutListener(this); // THIS IS THE PROGRAM THAT'S MAKING THE SOUND
    settings.sampleRate = 48000; // sampling rate?
    settings.numOutputChannels = 2; // stereo audio output
    settings.numInputChannels = 0; // no input
    settings.bufferSize = 64; // signal vector size
    
    soundStream.setup(settings); // run the settings
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawEllipse(ofGetMouseX(), ofGetMouseY(), 50, 50);
    mx = ofClamp(ofGetMouseX()/(float)ofGetWidth(), 0., 1.);
    my = ofClamp(ofGetMouseY()/(float)ofGetHeight(), 0., 1.);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

// this is our audio loop
void ofApp::audioOut(ofSoundBuffer &buffer) {
    float volume = 1.0-my;
    float pan = mx;
    float outs = 0.; // output sample
    
    // the number of frames = buffer size * the number of channels
    for(int i = 0;i<buffer.getNumFrames();i++)
    {
        outs = ofRandom(-1, 1); // NOISE!!!!
        buffer[i*buffer.getNumChannels()] = outs * volume * sqrt(1.0-pan); // left
        outs = ofRandom(-1, 1); // MORE NOISE!!!!
        buffer[i*buffer.getNumChannels()+1] = outs * volume * sqrt(pan); // right
    }
}







// OTHER STUFF:

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
