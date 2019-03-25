#include "Mode.h"

class RedPulse: public Mode {
private:
    float level;
    int rate;
    int maxBrightness;
    bool asc;
    
public:
  RedPulse() : Mode() {
      level = 0.0;
      rate = 25;
      maxBrightness = 70;
      asc = true;
  }
  
  void get(long now, int rgb[]) {
      
      if (now % 2 == 0) {
          float step = float(rate) / 40.0;
          if (asc) {
              level += step;
              if (level >= maxBrightness) {
                  level = maxBrightness;
                  asc = false;
              }
          }
          else {
              level -= step;
              if (level <= 0) {
                  level = 1;
                  asc = true;
              }
          }
          rgb[0] = int(level);
          rgb[1] = 0;
          rgb[2] = 0;
      }
      
//    int step = (now/300) % 140;
//    if (step < 70) {
//      rgb[0] = step;
//    }
//    else {
//      rgb[0] = 140 - step;
//    }
//    if (rgb[0] == 0) {
//      rgb[0] = 1;
//    }
//    rgb[1] = 0;
//    rgb[2] = 0;
  }
  
  void adjust(char direction) {
    
  }
    void set(int level) {
        
    }
    void setState(int state) {
    }
    
    void setRate(int _rate) {
        rate = _rate;
        if (rate < 1) {
            rate = 1;
        }
        else if (rate > 100) {
            rate = 100;
        }
    }
    
    int getRate() {
        return rate;
    }

};
