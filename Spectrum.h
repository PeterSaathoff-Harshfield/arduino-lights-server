#include "Mode.h"

class Spectrum: public Mode {
private:
    int rate;
    int brightness;
public:
	Spectrum() : Mode() {
	  rate = 20;
        brightness = 63;
	}
  
  void get(long now, int rgb[]) {
      int n_steps = 999;
      int step = (now/rate) % n_steps;
      
      int s = step % int(n_steps/3);
      
      if (step >= 0 && step < int(n_steps/3)) {
          rgb[0] = int(brightness - brightness * s / (n_steps/3));
//          Serial.print("red    ");
//          Serial.println(rgb[0]);
          rgb[1] = int(brightness * s / (n_steps/3));
//          Serial.print("green    ");
//          Serial.println(rgb[1]);
          rgb[2] = 0;
      }
      else if (step >= int(n_steps/3) && step < 2*int(n_steps/3)) {
          rgb[0] = 0;
          rgb[1] = int(brightness - brightness * s / (n_steps/3));
          rgb[2] = int(brightness * s / (n_steps/3));
      }
      else if (step >= 2*int(n_steps/3) && step < n_steps) {
          rgb[0] = int(brightness * s / (n_steps/3));
          rgb[1] = 0;
          rgb[2] = int(brightness - brightness * s / (n_steps/3));
      }
      // original code, assumes n_steps = 768
//    if (step >= 0 && step < 256) {
//      rgb[0] = 255 - s;
//      rgb[1] = s;
//      rgb[2] = 0;
//    }
//    else if (step >= 256 && step < 512) {
//      rgb[0] = 0;
//      rgb[1] = 255 - s;
//      rgb[2] = s;
//    }
//    else if (step >= 512 && step < 768) {
//      rgb[0] = s;
//      rgb[1] = 0;
//      rgb[2] = 255 - s;
//    }
  }
  
  void adjust(char direction) {
    if (direction == 'l') {
      rate += 10;
    }
    else if (direction == 'r') {
      rate -= 10;
    }
  
    if (rate < 5) {
      rate = 5;
    }
    else if (rate > 500) {
      rate = 500;
    }
  
    Serial.print("spectrum rate: ");
    Serial.println(rate);
  }
  void setRate(int level) {
      rate = level;
      if (rate < 5) {
          rate = 5;
      }
      else if (rate > 500) {
          rate = 500;
      }
  }
    void setBrightness(int _brightness) {
        brightness = _brightness;
        if (brightness < 10) {
            brightness = 10;
        } 
        else if (brightness > 255) {
            brightness = 255;
        }
    }
    
    int getRate() {
        return rate;
    }
    
    int getMaxBrightness() {
        return brightness;
    }
};
