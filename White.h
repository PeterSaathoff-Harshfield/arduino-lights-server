#include "Mode.h"

class White: public Mode {
private:
    int brightness;
    
  
public:
    
  White() : Mode() {
    brightness = 50;
  }
  
  ~White() {}
  
  void get(long now, int rgb[]) {
    for (int i = 0; i < 3; i++) {
      rgb[i] = int(brightness * 2.55);
    }
  }
  
    void setBrightness(int level) {
        brightness = level;
        if (brightness < 0) {
            brightness = 0;
        }
        else if (brightness > 99) {
            brightness = 99;
        }

    }
    
  void adjust(char direction) {
    if (direction == 'l') {
      brightness -= 10;
    }
    else if (direction == 'r') {
      brightness += 10;
    }
  
    if (brightness < 0) {
      brightness = 0;
    }
    else if (brightness > 99) {
      brightness = 99;
    }
  
    Serial.print("white level: ");
    Serial.println(brightness);
  }
    
    int getBrightness() {
        return brightness;
    }
};
