#include "ofApp.hpp"

//--------------------------------------------------------------
void ofApp::setup() {
    sound.load("beat.wav");           // Loads a sound file (in bin/data/)
    sound.setLoop(true);              // Makes the song loop indefinitely
    sound.setVolume(1);               // Sets the song volume 
}

//--------------------------------------------------------------
void ofApp::update() {
    /* The update method is called muliple times per second
    It's in charge of updating variables and the logic of our app */
    ofSoundUpdate();                    // Updates all sound players
    if (!paused) {
        visualizer.updateAmplitudes();  // Updates Amplitudes for visualizer
    }
    progress = sound.getPosition();

    // loop
    if (loop && progress >= .99) {
        if (song_index < (int)(songs.size() - 1)) {
            changeSong(songs[song_index + 1]);
            song_index++;
        } else {
            song_index = 0;
            changeSong(songs[song_index]);
        }
    }

    // repeat
    if (repeat && progress >= .99) {
        changeSong(songs[song_index]);
    }

    //shuffle
    if (shuffle) {
        changeSong(songs[ofRandom(songs.size())]);
        shuffle = false;
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    /* The update method is called muliple times per second
    It's in charge of drawing all figures and text on screen */

    // Progress Bar
    ofSetColor(256);
    ofFill();
    float pos = playing ? progress : lastPos;
    int percent = pos * 100;
    ofDrawBitmapString("Song Progress: " + ofToString(percent) + "%", 0, 30);
    ofDrawRectangle(0,45,ofGetWidth()*pos,25); 

    // Mode Selection
    if (!playing) {
        ofDrawBitmapString("Press 'p' to play some music!", ofGetWidth() / 2 - 50, ofGetHeight() / 2);
    }
    vector<float> amplitudes = visualizer.getAmplitudes();
    if (mode == '1') {
        visualizer.setBands(256);
        drawMode1(amplitudes);
        ofSetBackgroundColor(ofColor::darkGreen); // Sets the Background Color
    } else if (mode == '2') {
        drawMode2(amplitudes);
        ofSetBackgroundColor(ofColor::darkSlateBlue); // Sets the Background Color
    } else if (mode == '3') {
        drawMode3(amplitudes);
        ofSetBackgroundColor(ofColor::darkMagenta); // Sets the Background Color
    } else if (mode == '4') {
        drawMode4(amplitudes);
        ofSetBackgroundColor(ofColor::darkRed); // Sets the Background Color
    }

    // adds visuals for modes
    if (loop) {
        ofSetColor(0, 0, 200);
        ofDrawBitmapString("Loop", 0, 85);
    } else {
        ofSetColor(200, 0, 0);
        ofDrawBitmapString("Loop", 0, 85);
    }
    if (repeat) {
        ofSetColor(0, 0, 200);
        ofDrawBitmapString("Repeat   (This is on by default)", 0, 100);
    } else {
        ofSetColor(200, 0, 0);
        ofDrawBitmapString("Repeat   (This is on by default)", 0, 100);
    }

    // adds the keys and their uses as visuals
    ofSetColor(256);
    ofDrawBitmapString("[a] Pause", 0, ofGetHeight() - 90);
    ofDrawBitmapString("[l] Loop", 0, ofGetHeight() - 75);
    ofDrawBitmapString("[r] Repeat", 0, ofGetHeight() - 60);
    ofDrawBitmapString("[b] Shuffle", 0, ofGetHeight() - 45);
    ofDrawBitmapString("[!] Song 1", 150, ofGetHeight() - 90);
    ofDrawBitmapString("[@] Song 2", 150, ofGetHeight() - 75);
    ofDrawBitmapString("[#] Song 3", 150, ofGetHeight() - 60);
    ofDrawBitmapString("[$] Song 4", 150, ofGetHeight() - 45);
    ofDrawBitmapString("[%] Song 5", 150, ofGetHeight() - 30);
    ofDrawBitmapString("[-] Volume Down", 300, ofGetHeight() - 90);
    ofDrawBitmapString("[=] Volume Up", 300, ofGetHeight() - 75);
    ofDrawBitmapString("[1] Mode 1", 450, ofGetHeight() - 90);
    ofDrawBitmapString("[2] Mode 2", 450, ofGetHeight() - 75);
    ofDrawBitmapString("[3] Mode 3", 450, ofGetHeight() - 60);
    ofDrawBitmapString("Volume" + to_string(sound.getVolume()) + "%", 700, ofGetHeight() - 90);


    // ofDrawBitmapString("Current Mouse Position: " + ofToString(cur_x) + ", " + ofToString(cur_y), 0, 30);    //used for debugging
}
void ofApp::drawMode1(vector<float> amplitudes) {
    ofFill();        // Drawn Shapes will be filled in with color
    ofSetColor(256); // This resets the color of the "brush" to white
    ofDrawBitmapString("Rectangle Height Visualizer", 0, 15);
    ofSetColor(ofColor::blueSteel);
    float width_visual = ofGetWidth() / amplitudes.size();
    float rectPosition = 0.0; 
    for (float amp : amplitudes){
        ofDrawRectRounded(rectPosition,ofGetHeight()-125, width_visual, amp - 10, 10);
        rectPosition += width_visual;

    }
}

void ofApp::drawMode2(vector<float> amplitudes) {
    ofSetLineWidth(5); // Sets the line width
    ofNoFill();        // Only the outline of shapes will be drawn
    ofSetColor(256);   // This resets the color of the "brush" to white
    ofDrawBitmapString("Circle Radius Visualizer", 0, 15);
    int bands = amplitudes.size();
    for (int i = 0; i < bands; i++) {
        ofSetColor((bands - i) * 32 % 256, 18, 144); // Color varies between frequencies
        ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, amplitudes[0] / (i + 1));
    }
}

void ofApp::drawMode3(vector<float> amplitudes) {
    ofSetColor(256);   // This resets the color of the "brush" to white
    ofDrawBitmapString("Curve Visualizer", 0, 15);
    ofSetColor(ofColor::orange);
    float width_visual = ofGetWidth() / 64.0;
    float position = 0.0; 
    for (float amp : amplitudes){
        ofDrawCurve(position, 20*amp, 0, ofGetHeight()/2, ofGetWidth(), ofGetHeight()/2, position, -20*amp);
        position += width_visual;
    }
}

void ofApp::drawMode4(vector<float> amplitudes) {
    ofSetColor(256);   // This resets the color of the "brush" to white
    ofDrawBitmapString("Elipse Visualizer/Cool Visualizer", 0, 15);
    ofSetColor(ofColor::lightGreen);
    float width_visual = ofGetWidth() / 64.0;
    float position = 0.0; 
    for (float amp : amplitudes){
        ofDrawEllipse(ofGetWidth() / 2, ofGetHeight() / 2, position, amp);
        position += width_visual;

    }
}

//--------------------------------------------------------------
void ofApp::changeSong(string filename){ 
    sound.load(filename);
    sound.play();
    playing = true;
    paused = false;
    sound.setLoop(true);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    // This method is called automatically when any key is pressed
    switch (key) {
    case 'p':
        if (playing) {
            sound.stop();
        } else {
            sound.play();
        }
        playing = !playing;
        break;
    case 'a':
        paused = !paused;
        break;
    case 'l':
        loop = !loop;
        if (repeat) {
            repeat = !repeat;
        }
        break;
    case 'r':
        repeat = !repeat;
        if (loop) {
            loop = !loop;
        }
        break;
    case 'b':
        shuffle = !shuffle;
        break;
    case '!':
        changeSong(songs[0]);
        break;
     case '@':
        changeSong(songs[1]);
        break; 
    case '#':
        changeSong(songs[2]);
        break; 
    case '$':
        changeSong(songs[3]);
        break; 
    case '%':
        changeSong(songs[4]);
        break;
    case '=':
        sound.setVolume(min(sound.getVolume()+0.1,1.0));
        break;
    case '-':
        sound.setVolume(max(sound.getVolume()-0.1,0.0));
        break;
    case '1':
        mode = '1';
        break;
    case '2':
        mode = '2';
        break;
    case '3':
        mode = '3';
        break;
    case '4':
        mode = '4';
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    cur_x = x;
    cur_y = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    // if moused clicked and dragged at the progress bar then it will alter the progress
    if ((y <= 70) && (y >= 45)) {
        float newProgress = ofMap(x, 0, ofGetWidth(), 0, 1);
        sound.setPosition(newProgress);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
}
//--------------------------------------------------------------