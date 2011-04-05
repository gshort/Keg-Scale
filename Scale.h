#ifndef Scale_h
#define Scale_h

#include "WProgram.h"

class Scale {
  public:
    Scale(int a_in, int a_out, int d_out, int samples, float threshold);
    int sample();
    void display();
    bool checkConnection();
    int tareLow();
    int tareHigh();
    void windUp(int stepDelay);
    void windDown(int stepDelay);
   private:
     int a_in;
     int a_out;
     int d_out;
     int samples;
     float threshold;
     float current;
     int lowTare;
     int highTare;
};

#endif
