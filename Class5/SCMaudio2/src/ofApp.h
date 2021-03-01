#pragma once

#include "ofMain.h"

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

    float mx, my; // scaled mouse positions
    
    int mode; // switch sound generators
    float SI; // sampling increment
    float p = 0; // phasor position
    float p2 = 1; // phasor position 2
    int SR = 48000; // sampling rate
    int bufsize = 512; // buffer size
    // onepole sample memory (STEREO)
    float pprevL = 0; // y(n-1) across buffers
    float pprevR = 0; // y(n-1) across buffers
    // biquad sample memory
    float xpn = 0; // x(n-1) across buffers
    float xppn = 0; // x(n-2) across buffers
    float ypn = 0; // y(n-1) across buffers
    float yppn = 0; // y(n-2) across buffers
    vector <float> lAudio;
    vector <float> rAudio;
    string label;
    // audio stuff:
    void audioOut(ofSoundBuffer &buffer); // perform loop - "draw" for audio
    ofSoundStream soundStream; // HAL - hardware abstraction layer for audio
    double mtof(double m);
};
