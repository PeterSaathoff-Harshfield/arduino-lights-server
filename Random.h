#include "Mode.h"

class Random: public Mode {
private:
  int rate;
  
    int maxBrightness;
    
public:
  Random() : Mode() {
    rate = 32;
      
      maxBrightness = 765;
  }
  
  void get(long now, int rgb[]) {
    int step = (now/20) % rate;
    if (step == 0) {
      rgb[0] = random() % int(maxBrightness / 3);
      rgb[1] = random() % int(maxBrightness / 3);
      rgb[2] = random() % int(maxBrightness / 3);
    }
  }
  
  void adjust(char direction) {
    if (direction == 'l') {
      rate -= 2;
    }
    else if (direction == 'r') {
      rate += 2;
    }
    
    if (rate <= 4) {
      rate = 4;
    }
    else if (rate > 300) {
      rate = 300;
    }
  }
    void set(int level) {
        rate = level;
        if (rate <= 4) {
            rate = 4;
        }
        else if (rate >= 1000) {
            rate = 1000;
        }

    }
    void setState(int state) {
    }

    void setMaxBrightness(int max) {
        maxBrightness = max;
        if (maxBrightness > 765) {
            maxBrightness = 765;
        }
        else if (maxBrightness < 42) {
            maxBrightness = 42;
        }
    }
    
    int getRate() {
        return rate;
    }
    
    int getMaxBrightness() {
        return maxBrightness;
    }
};
