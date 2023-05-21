#pragma once

#include "AudioVisualizer.hpp"
#include "ofMain.h"

class ofApp : public ofBaseApp {

  private:
    ofSoundPlayer sound;
    AudioVisualizer visualizer;
    vector<string>songs = {"beat.wav","geesebeat.wav","pigeon_coo.wav","rock-song.wav", "Metro_Boomin.wav"};

    bool playing = false;
    bool paused = false;
    bool loop = false;
    bool repeat = true;
    bool shuffle = false;
    char mode = '1'; 
    int song_index= 0 ;
    

    
    int cur_x, cur_y = 0;
    float sound_length;

    float progress = 0;
    float lastPos = 0;

  public:
    void setup();
    void update();
    void draw();

    void drawMode1(vector<float> amplitudes);
    void drawMode2(vector<float> amplitudes);
    void drawMode3(vector<float> amplitudes);
    void drawMode4(vector<float> amplitudes);

    void changeSong(string filename);

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
};
