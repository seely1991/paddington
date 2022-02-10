#ifndef STATE_H__
#define STATE_H__
#include <iostream>
class State {
public:
    State();
    bool GetRecording(){return recording;};
    bool GetPlaying() {return playing;};
    int GetDubLength() {return dub_length;};
    bool GetOutput2() {return output2_bypass;};
    int GetVolume() {return volume;};
    int GetSwell() {return swell_length;};
    //GetReverbVal();
    //GetFadeVal();
    
    void SetRecording() {recording = !recording;};
    void SetPlaying() {playing = !playing;};
    void SetDubLength(int length) {dub_length = length;};
    void SetOutput2() {output2_bypass = !output2_bypass;};
    void SetVolume(int val) {volume = val;};
    void SetSwell(int val) {swell_length = val;};
    
    void hello() {std::cout << "hello" << std::endl;}
    
private:
    bool recording;        //is it in recording state
    bool playing;          //is it in playing state
    int dub_length;        //length of record time before looping
    bool output2_bypass;   //does the output include bypass?
    int volume;            //volume of effect
    int swell_length;  //length of swell in milliseconds

    //int reverb;        //amount of reverb (wet/dry> decay time?)
    //int fade_length;   //fades out when initiated (inverse log)
};

#endif