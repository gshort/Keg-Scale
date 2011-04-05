#include "WProgram.h"
#include "Scale.h"

Scale::Scale(int a_in, int a_out, int d_out, int samples, float threshold) {
  this->a_in = a_in;
  this->a_out = a_out;
  this->d_out = d_out;
  this->samples = samples;
  this->threshold = threshold;
  this->current = 0;
  this->lowTare = 0;
  this->highTare = 1023;
  pinMode(this->a_in, INPUT);
  pinMode(this->a_out, OUTPUT);
  pinMode(this->d_out, OUTPUT);
}

int Scale::sample() {
  float sum = 0.0;
  for(int ii = 0; ii < this->samples; ++ii) {
    sum += analogRead(this->a_in);
  }
  int val = sum / float(this->samples);
  if(abs(this->current - val) > int(float(this->current) * this->threshold)) {
    this->current = val;
  }
  return this->current;
}

void Scale::display() {
  if(this->checkConnection()) {
    digitalWrite(this->d_out, HIGH);
  } else {
    digitalWrite(this->d_out, LOW);
  }
  analogWrite(this->a_out, this->current);
}

bool Scale::checkConnection() {
  return analogRead(this->a_in);
}

int Scale::tareLow() {
  this->windUp(2);
  this->lowTare = this->sample();
  this->windDown(2);
}

int Scale::tareHigh() {
  this->windUp(2);
  this->highTare = this->sample();
  this->windDown(2);
}

void Scale::windUp(int stepDelay) {
  for(int ii = 0; ii < 1024; ++ii) {
    analogWrite(this->a_out, ii);
    delay(stepDelay);
  }
}

void Scale::windDown(int stepDelay) {
  for(int ii = 1023; ii >= 0; --ii) {
    analogWrite(this->a_out, ii);
    delay(stepDelay);
  }
}


