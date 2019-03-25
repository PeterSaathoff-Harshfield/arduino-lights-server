#include "Mode.h"

class Random: public Mode {
private:
  int rate;
  int maxBrightness;
  int progressToNext;
    
public:
  Random() : Mode() {
    rate = 30;
    maxBrightness = 80;
    progressToNext = 0;
  }
  
  void get(long now, int rgb[]) {
      
      if (now % 2 == 0) {
          
          int step = int(float(rate) / 3.0);
          
          progressToNext += step;
          if (progressToNext >= 300) {
              progressToNext = 0;
              
              float scalar = float(maxBrightness) / 100.0;
              
              rgb[0] = int(random() % int(scalar * float(255)));
              rgb[1] = int(random() % int(scalar * float(255)));
              rgb[2] = int(random() % int(scalar * float(255)));
          }
      }
      
//    int step = (now/20) % rate*3;
//    if (step == 0) {
//      rgb[0] = random() % int(maxBrightness * 2.55);
//      rgb[1] = random() % int(maxBrightness * 2.55);
//      rgb[2] = random() % int(maxBrightness * 2.55);
//    }
  }
  
  void adjust(char direction) {
    if (direction == 'l') {
      rate -= 2;
    }
    else if (direction == 'r') {
      rate += 2;
    }
    
    if (rate < 1) {
      rate = 1;
    }
    else if (rate > 100) {
      rate = 100;
    }
  }
    void set(int level) {
        rate = level;
        if (rate < 1) {
            rate = 1;
        }
        else if (rate > 100) {
            rate = 100;
        }

    }

    void setMaxBrightness(int max) {
        maxBrightness = max;
        if (maxBrightness > 100) {
            maxBrightness = 100;
        }
        else if (maxBrightness < 3) {
            maxBrightness = 3;
        }
    }
    
    int getRate() {
        return rate;
    }
    
    int getMaxBrightness() {
        return maxBrightness;
    }
};
