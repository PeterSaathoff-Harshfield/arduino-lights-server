#include "Mode.h"

class Spectrum: public Mode {
private:
    int rate;
    int brightness;
    
    int sr;
    int sg;
    int sb;
    int smode;
    
public:
	Spectrum() : Mode() {
	  rate = 25;
      brightness = 99;
        
        sr = 255;
        sg = 0;
        sb = 0;
        smode = 0;
	}
  
  void get(long now, int rgb[]) {
      
      if (now % 2 == 0) {
          
          int step = int(float(rate)/20.0);
          
          if (smode == 0) {
              sr -= step;
              sg += step;
              if (sr <= 0) {
                  sr = 0;
                  sg = 255;
                  smode = 1;
              }
          }
          else if (smode == 1) {
              sg -= step;
              sb += step;
              if (sg <= 0) {
                  sg = 0;
                  sb = 255;
                  smode = 2;
              }
          }
          else { // smode == 2
              sb -= step;
              sr += step;
              if (sb <= 0) {
                  sb = 0;
                  sr = 255;
                  smode = 0;
              }
          }
          
          float scalar = float(brightness) / 100.0;
          
          rgb[0] = int(sr * scalar);
          rgb[1] = int(sg * scalar);
          rgb[2] = int(sb * scalar);
      }
  }
  
  void adjust(char direction) {
    if (direction == 'l') {
      rate += 10;
    }
    else if (direction == 'r') {
      rate -= 10;
    }
  
    if (rate < 1) {
      rate = 1;
    }
    else if (rate > 100) {
      rate = 100;
    }
  
    Serial.print("spectrum rate: ");
    Serial.println(rate);
  }
  void setRate(int level) {
      rate = level;
      if (rate < 1) {
          rate = 1;
      }
      else if (rate > 100) {
          rate = 100;
      }
  }
    
    void setBrightness(int _brightness) {
        brightness = _brightness;
        if (brightness < 5) {
            brightness = 5;
        } 
        else if (brightness > 99) {
            brightness = 99;
        }
    }
    
    int getRate() {
        return rate;
    }
    
    int getMaxBrightness() {
        return brightness;
    }
};
