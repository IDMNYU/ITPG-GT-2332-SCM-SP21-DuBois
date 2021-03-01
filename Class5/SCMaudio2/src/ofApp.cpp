#include "ofApp.h"

#define MAXVOL 0.5 // don't kill yourself

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
    settings.sampleRate = SR;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufsize; // signal vector size
    
    soundStream.setup(settings); // run the settings

    lAudio.assign(bufsize, 0.0);
    rAudio.assign(bufsize, 0.0);
    
    label = "hi there";

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    mx = ofClamp(ofGetMouseX()/(float)ofGetWidth(), 0., 1.);
    my = ofClamp(ofGetMouseY()/(float)ofGetHeight(), 0., 1.);
    
    switch(mode)
    {
        case 0:
            label="noise";
            break;
        case 1:
            label="sine";
            break;
        case 2:
            label="sawtooth";
            break;
        case 3:
            label="triangle";
            break;
        case 4:
            label="square w/PWM";
            break;
        case 5:
            label="square w/one pole LPF";
            break;
        case 6:
            label="sawtooth w/biquad LPF";
            break;
        default:
            label="hi there";
            break;
    }
    ofDrawBitmapString(label, 20, 20);

    
    // this stuff might do something:
    ofNoFill();
    
    // draw the left channel:
    ofPushStyle();
        ofPushMatrix();
        ofTranslate(32, 150, 0);
            
        ofSetColor(225);
        ofDrawBitmapString("Left Channel", 4, 18);
        
        ofSetLineWidth(1);
        ofDrawRectangle(0, 0, 900, 200);

        ofSetColor(245, 58, 135);
        ofSetLineWidth(3);
                    
            ofBeginShape();
            for (unsigned int i = 0; i < lAudio.size(); i++){
                float x =  ofMap(i, 0, lAudio.size(), 0, 900, true);
                ofVertex(x, 100 -lAudio[i]*180.0f);
            }
            ofEndShape(false);
            
        ofPopMatrix();
    ofPopStyle();

    // draw the right channel:
    ofPushStyle();
        ofPushMatrix();
        ofTranslate(32, 350, 0);
            
        ofSetColor(225);
        ofDrawBitmapString("Right Channel", 4, 18);
        
        ofSetLineWidth(1);
        ofDrawRectangle(0, 0, 900, 200);

        ofSetColor(245, 58, 135);
        ofSetLineWidth(3);
                    
            ofBeginShape();
            for (unsigned int i = 0; i < rAudio.size(); i++){
                float x =  ofMap(i, 0, rAudio.size(), 0, 900, true);
                ofVertex(x, 100 -rAudio[i]*180.0f);
            }
            ofEndShape(false);
            
        ofPopMatrix();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    mode = (mode+1)%7;

}

// this is our audio loop
void ofApp::audioOut(ofSoundBuffer &buffer) {
    
    float outs = 0.; // output sample
    float volume; // volume
    
    if(mode==0) // NOISE
    {
        float pan = mx;
        volume = sqrt(1.0-my)*MAXVOL;
        
        // the number of frames = buffer size * the number of channels
        for(int i = 0;i<buffer.getNumFrames();i++)
        {
            outs = ofRandom(-1, 1);
            buffer[i*buffer.getNumChannels()] = outs * volume * sqrt(1.0-pan); // left
            outs = ofRandom(-1, 1);
            buffer[i*buffer.getNumChannels()+1] = outs * volume * sqrt(pan); // right
        }
    }
    else if(mode==1) // SINE WAVE
    {
        float freq = mtof(mx*60+30);
        float SI = freq*2*M_PI/(float)SR;
        volume = sqrt(1.0-my)*MAXVOL;
        
        // the number of frames = buffer size * the number of channels
        for(int i = 0;i<buffer.getNumFrames();i++)
        {
            outs = sin(p);
            buffer[i*buffer.getNumChannels()] = outs * volume; // left
            buffer[i*buffer.getNumChannels()+1] = outs * volume; // right
            p = fmod(p+SI, 2*M_PI); // floating point modulo
        }
    }
    else if(mode==2) // SAW WAVE
    {
        float freq = mtof(mx*60+30);
        float SI = freq*2*M_PI/(float)SR;
        volume = sqrt(1.0-my)*MAXVOL;

        // the number of frames = buffer size * the number of channels
        for(int i = 0;i<buffer.getNumFrames();i++)
        {
            outs = p-1.0;
            buffer[i*buffer.getNumChannels()] = outs * volume; // left
            buffer[i*buffer.getNumChannels()+1] = outs * volume; // right
            p = fmod(p+SI, 2); // floating point modulo
        }
    }
    else if(mode==3) // TRIANGLE
    {
        float freq = mtof(mx*60+30);
        float SI = freq*2*M_PI/(float)SR;
        volume = sqrt(1.0-my)*MAXVOL;

        // the number of frames = buffer size * the number of channels
        for(int i = 0;i<buffer.getNumFrames();i++)
        {
            outs = p<1?p:2.0-p; // triangle
            outs = outs*2.0-1.0; // scale to -1 to 1
            buffer[i*buffer.getNumChannels()] = outs * volume; // left
            buffer[i*buffer.getNumChannels()+1] = outs * volume; // right
            p = fmod(p+SI, 2); // floating point modulo
        }
    }
    else if(mode==4) // SQUARE
    {
        float freq = mtof(mx*60+30);
        float SI = freq*2*M_PI/(float)SR;
        float pwmval;
        volume = sqrt(1.0-my)*MAXVOL;

        // the number of frames = buffer size * the number of channels
        for(int i = 0;i<buffer.getNumFrames();i++)
        {
            pwmval = sin(p2)*0.5+0.5; // sine from 0-1
            outs = p>pwmval?1:-1;
            buffer[i*buffer.getNumChannels()] = outs * volume; // left
            buffer[i*buffer.getNumChannels()+1] = outs * volume; // right
            p = fmod(p+SI, 2); // floating point modulo
            p2 = fmod(p2+0.0001, 2*M_PI); // PWM
        }
    }
    else if(mode==5) // STEREO SQUARE w/ ONE POLE FILTER
    {
        float freq = mtof(mx*60+30);
        float SI = freq*2*M_PI/(float)SR;
        float a = 1.0-my; // feedback coefficient
        volume = 0.3*MAXVOL;
        float pwmval, squareout;

        // the number of frames = buffer size * the number of channels
        for(int i = 0;i<buffer.getNumFrames();i++)
        {
            pwmval = sin(p2)*0.5+0.5; // sine from 0-1
            squareout = p>pwmval?1:-1;
            outs = a * squareout + (1.-a)*pprevL;
            buffer[i*buffer.getNumChannels()] = outs * volume; // left
            pprevL = outs;
            squareout = p>(1.0-pwmval)?1:-1;
            outs = a * squareout + (1.-a)*pprevR;
            buffer[i*buffer.getNumChannels()+1] = outs * volume; // right
            pprevR = outs;
            p = fmod(p+SI, 2); // floating point modulo
            p2 = fmod(p2+0.0001, 2*M_PI); // PWM
        }
    }
    else if(mode==6) // SAW w/ BIQUAD FILTER
    {
        // sawtooth wave
        float freq = mtof(mx*60+30);
        float SI = freq*2*M_PI/(float)SR;
        volume = 0.3*MAXVOL;

        // biquad: params
        float f0 = mtof((1.0-my)*100+30);
        float dB = 0.; // gain for peaking / shelving
        float Q = 12.; // width / resonance of filter

        // biquad: intermediates
        float A = sqrt(pow(10, dB/20)); // amplitude
        float w0 = 2*PI*f0/SR; // filter increment in radians
        float cw0 = cos(w0); // cosine of w0 - precompute
        float sw0 = sin(w0); // sine of w0 - precompute
        float alpha = sin(w0)/(2*Q); // alpha term - precompute
        float soff = 2*sqrt(A)*alpha; // shelving offset - precompute
        
        // biquad: low pass coefficients
        float b0 =  (1 - cw0)/2;
        float b1 =   1 - cw0;
        float b2 =  (1 - cw0)/2;
        float a0 =   1 + alpha;
        float a1 =  -2 * cw0;
        float a2 =   1 - alpha;
        
        float xn, yn; // input and output sample

        // the number of frames = buffer size * the number of channels
        for(int i = 0;i<buffer.getNumFrames();i++)
        {
            xn = p-1.; // sawtooth in
            
            // biquad
            yn = (b0/a0)*xn + (b1/a0)*xpn + (b2/a0)*xppn - (a1/a0)*ypn - (a2/a0)*yppn;
            // copy to output
            outs = yn;
            
            buffer[i*buffer.getNumChannels()] = outs * volume; // left
            buffer[i*buffer.getNumChannels()+1] = outs * volume; // right
            p = fmod(p+SI, 2); // floating point modulo
            
            // shift:
            xppn = xpn;
            xpn = xn;
            yppn = ypn;
            ypn = yn;
        }
    }

    // ONE LAST LOOP FOR VISUALS
    for(int i = 0;i<buffer.getNumFrames();i++)
    {
        lAudio[i] = buffer[i*buffer.getNumChannels()]; // left
        rAudio[i] = buffer[i*buffer.getNumChannels()+1]; // right
    }


}


double ofApp::mtof(double m)
{
    // midi to frequency converter
    return(440. * exp(0.057762265 * (m-69.)));
    
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
