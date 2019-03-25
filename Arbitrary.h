#include "Mode.h"

class Arbitrary: public Mode {
private:
  
    int red;
    int green;
    int blue;
    
//    int hue
    
public:
  Arbitrary() : Mode() {
      int red = 64;
      int green = 64;
      int blue = 64;
      
//      int hue = 
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
    
    void setHue(int h) {
        int subh = h % 256;
        if (h >= 0 && h < 256) {
            red = 256 - subh;
            green = subh;
            blue = 0;
        }
        else if (h > 255 && h < 512) {
            red = 0;
            green = 256 - subh;
            blue = subh;
        }
        else if (h > 511 && h < 768) {
            red = subh;
            green = 0;
            blue = 256 - subh;
        }
        
//        hue = h;
//        if (hue >= 768) {
//            hue = 768;
//        }
//        else if (hue < 0) {
//            hue = 0;
//        }
    }
    
};
