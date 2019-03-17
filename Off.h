#include "Mode.h"

class Off: public Mode {
private:
  
  
public:
    
  Off() : Mode() {
    
  }
  
  ~Off() {}
    
  void adjust(char direction) {
  }
  
  void get(long now, int rgb[]) {
    for (int i = 0; i < 3; i++) {
      rgb[i] = 0;
    }
  }
  
};
