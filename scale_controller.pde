#include "Scale.h"

#define SAMPLES 1000   // number of samples per reading
#define THRESHOLD 0.1  // minimum percentage change between readings to be considered different
#define NUM_SCALES 6   // maximum number of scales; this assumes an arduino uno (or similar)

// list of pins for use by scales: analog in, analog out, digital out
int a_in[] = {A0, A1, A2, A3, A4, A5};
int a_out[] = {3, 5, 6, 9, 10, 11};
int d_out[] = {2, 4, 7, 8, 12, 13};
int th = 0;
in tl = 1;

Scale* scales[6];

void setup() {
  for(int ii = 0; ii < NUM_SCALES; ++ii) {
    scales[ii] = &Scale(a_in[ii], a_out[ii], d_out[ii], SAMPLES, THRESHOLD);
    scales[ii]->windUp(1);
    scales[ii]->windDown(1);
  }
}

void loop() {
  for(int ii = 0; ii < NUM_SCALES; ++ii) {
    if(scales[ii]->checkConnection()) {
      scales[ii]->sample();
    }
    scales[ii]->display();
  }
}
