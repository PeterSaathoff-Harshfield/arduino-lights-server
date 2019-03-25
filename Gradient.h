#include "Mode.h"

class Gradient: public Mode {
private:
  int gradientState;
  int rate;
  int brightness;
  int numberOfGradients;
    
    bool mode0;
    bool mode1;
    bool mode2;
  
    float m0r;
    float m0b;
    float m1g;
    float m1b;
    float m2g;
    float m2r;
    
public:
  Gradient() : Mode() {
    gradientState = 0;
    rate = 30;
    brightness = 80;
    numberOfGradients = 3;
      
      mode0 = true;
      mode1 = true;
      mode2 = true;
      
      m0r = 0.0;
      m0b = 255.0;
      m1g = 0.0;
      m1b = 255.0;
      m2r = 255.0;
      m2g = 0.0;
  }
  
  void get(long now, int rgb[]) {
      
      if (now % 2 == 0) {
          
          float step = float(rate) / 20.0;
          
          float scalar = float(float(brightness) / 100.0);
          
//          Serial.println(brightness);
//          Serial.println(scalar);
//          Serial.println(gradientState);
          
          if (gradientState == 0) {
//              Serial.println(mode0);
              if (mode0) {
                  m0r += step;
                  m0b -= step;
                  if (m0r >= 255 || m0b <= 0) {
                      m0r = 255;
                      m0b = 0;
                      mode0 = false;
                  }
              }
              else {
                  m0r -= step;
                  m0b += step;
                  if (m0b >= 255 || m0r <= 0) {
                      m0r = 0;
                      m0b = 255;
                      mode0 = true;
                  }
              }
              rgb[0] = int(m0r * scalar);
              rgb[1] = 0;
              rgb[2] = int(m0b * scalar);}
          
          else if (gradientState == 1) {
              if (mode1) {
                  m1g += step;
                  m1b -= step;
                  if (m1g >= 255 || m1b <= 0) {
                      m1g = 255;
                      m1b = 0;
                      mode1 = false;
                  }
              }
              else {
                  m1g -= step;
                  m1b += step;
                  if (m1b >= 255 || m1g <= 0) {
                      m1b = 255;
                      m1g = 0;
                      mode1 = true;
                  }
              }
              rgb[0] = 0;
              rgb[1] = int(m1g * scalar);
              rgb[2] = int(m1b * scalar);
          }
          else if (gradientState == 2) {
              if (mode2) {
                  m2r += step;
                  m2g -= step;
                  if (m2r >= 255 || m2g <= 0) {
                      m2r = 255;
                      m2g = 0;
                      mode2 = false;
                  }
              }
              else {
                  m2r -= step;
                  m2g += step;
                  if (m2g >= 255 || m2r <= 0) {
                      m2g = 255;
                      m2r = 0;
                      mode2 = true;
                  }
              } 
              rgb[0] = int(m2r * scalar);
              rgb[1] = int(m2g * scalar);
              rgb[2] = 0;
          }
      }
      
      
    
      
//    int step = (now/rate) % 512;
//    
//    int x;
//    int y;
//    if (step < 256) {
//      x = 255 - step;
//      y = step;
//    }
//    else if (step >= 256) {
//      x = step - 256;
//      y = 512 - step;
//    }
//    
//    if (gradientState == 0) {
//      rgb[0] = 0;
//      rgb[1] = x;
//      rgb[2] = y;
//    }
//    else if (gradientState == 1) {
//      rgb[0] = y;
//      rgb[1] = 0;
//      rgb[2] = x;
//    }
//    else if (gradientState == 2) {
//      rgb[0] = x;
//      rgb[1] = y;
//      rgb[2] = 0;
//    }
  }
  
  void adjust(char direction) {
    if (direction == 'l') {
      gradientState -= 1;
    }
    else if (direction == 'r') {
      gradientState += 1;
    }
    
    if (gradientState < 0) {
      gradientState = gradientState + numberOfGradients;
    }
    else if (gradientState >= numberOfGradients) {
      gradientState = gradientState % numberOfGradients;
    }
  }
    void set(int level) {
        
    }
    
    void setState(int state) {
        gradientState = state;
        if (gradientState < 0) {
            gradientState = gradientState + numberOfGradients;
        }
        else if (gradientState >= numberOfGradients) {
            gradientState = gradientState % numberOfGradients;
        }
    }
    
    void setRate(int level) {
        rate = level;
        if (rate < 5) {
            rate = 5;
        }
        else if (rate > 100) {
            rate = 100;
        }
    }
    
    void setBrightness(int level) {
        brightness = level;
        if (brightness < 5) {
            brightness = 5;
        }
        else if (brightness >= 100) {
            brightness = 100;
        }
    }
    
    int getState() {
        return gradientState;
    }
    
    int getRate() {
        return rate;
    }
    
    int getBrightness() {
        return brightness;
    }
};
