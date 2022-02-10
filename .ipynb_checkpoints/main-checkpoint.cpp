#include <iostream>
#include <math.h>
#include <chrono>
#include <sys/time.h>
#include <ctime>
#include <typeinfo>
#include "state.h"

//use JACK with raspberry pi 
//USB audio dongle for pi
//adapt this project: https://tibbbz.medium.com/guitarix-the-pi-dle-board-8d6298ca8e42

int readPot(int pin) {
    //return the resistance reading of pin
    return 500;
}

bool readSwitch(int pin) {
    //return open or closed reading of pin
    return false;
}

int timeNow() {
    return abs(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

void logSwell(float c, State &state, bool inverted) {
    // c is the time taken to get to full (in milliseconds)
    // 0 < c < 3000?
    
    //read the pot level;
    int potLevel = readPot(4);
    
    //how much curve there is
    float b = 1000;  // 1 < b < 100
    float y = 0;
    int init_millis = timeNow();
    int duration = 0;
    
    //how long to wait before setting the volume again;
    //shorter delay is smoother but uses more cpu
    int delay = 5;
    
    //volume when function will be completed
    int target_vol;
    if (inverted) {
        target_vol = 0;
    }else{
        target_vol = potLevel;
        //if not inverted, should start volume at 0
        state.SetVolume(0);
    }
    while (duration <= c && state.GetVolume() != target_vol) {
        //y = (b^(x/c) - 1) / (b - 1)
        if (timeNow() - init_millis - duration >= delay) {
            int x = duration;
            if (inverted) {x = -1 * x + c;}    //transform reflection over y axis and translate to the right c
            float y = potLevel * (pow(b,x/c)-1)/(b-1);    //y = (b^(x/c) - 1) / (b - 1)
            if (abs(floor(y - state.GetVolume())) >= 1){
                state.SetVolume(y);
                std::cout << "volume is: " << state.GetVolume() << "    x is: " << x << "     and y is: " << y << std::endl;
            }
            duration = timeNow() - init_millis;
        }
    }
    //if duration jumps above c, it's possible last volume written is not the target volume
    //set volume after function to ensure target volume has been reached
    state.SetVolume(target_vol);
    std::cout << state.GetVolume() << std::endl;
}

void recordSound(int duration) {
    //the looping function, set to repeat according to duration;
}

int main() {
    State globalState;
    
    logSwell(4000, globalState, false);
    logSwell(2000, globalState, true);
    
    return 0;

}