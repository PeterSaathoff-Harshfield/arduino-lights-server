#include "Mode.h"

class Arbitrary: public Mode {
private:
  
    int red;
    int green;
    int blue;
    
public:
  Arbitrary() : Mode() {
      int red = 64;
      int green = 64;
      int blue = 64;
  }
  
  ~Arbitrary() {}
  
  void get(long now, int rgb[]) {
    rgb[0] = red;
    rgb[1] = green;
    rgb[2] = blue;
  }
  
    void adjust(char direction) {
    }
    
    void set(int r, int g, int b) {
        red = r;
        green = g;
        blue = b;
    }
    void setR(int r) {
        if (r < 0) {
            red = 0;
        }
        else if (r >= 255) {
            red = 255;
        }
        red = r;
    }
    void setG(int g) {
        if (g < 0) {
            green = 0;
        }
        else if (g >= 255) {
            green = 255;
        }
        green = g;
    }
    void setB(int b) {
        if (b < 0) {
            blue = 0;
        }
        else if (b > 255) {
            blue = 255;
        }
        blue = b;
    }
};
