#include "Mode.h"

class Flow: public Mode {
private:
    int rate;
    int maxBrightness;
    
    bool r_asc;
    bool g_asc;
    bool b_asc;
    
    float r_f;
    float g_f;
    float b_f;
    
public:
  Flow() : Mode() {
    rate = 8;
    maxBrightness = 255;
    r_asc = true;
    g_asc = true;
    b_asc = true;
      
      r_f = 0;
      g_f = 0;
      b_f = 0;
      
  }
  
  void get(long now, int rgb[]) {
      
      if (now % 2 == 0) {
          float r_step = float(rate) / 10.0;
          float g_step = float(rate) / 13.5;
          float b_step = float(rate) / 6.9;
          
          if (r_asc) {
              r_f += r_step;
              if (r_f >= 255) {
                  r_f = 255;
                  r_asc = false;
              }
          }
          else {
              r_f -= r_step;
              if (r_f <= 64) {
                  r_f = 64;
                  r_asc = true;
              }
          }
          if (g_asc) {
              g_f += g_step;
              if (g_f >= 255) {
                  g_f = 255;
                  g_asc = false;
              }
          }
          else {
              g_f -= g_step;
              if (g_f <= 64) {
                  g_f = 64;
                  g_asc = true;
              }
          }
          if (b_asc) {
              b_f += b_step;
              if (b_f >= 255) {
                  b_f = 255;
                  b_asc = false;
              }
          }
          else {
              b_f -= b_step;
              if (b_f <= 64) {
                  b_f = 64;
                  b_asc = true;
              }
          }
          float scalar = float(maxBrightness / 100.0);
          rgb[0] = int(r_f * scalar);
          rgb[1] = int(g_f * scalar);
          rgb[2] = int(b_f * scalar);
      }
      
//    int step = (now) % rate;
//    if (step == 0) {
//      
//        int x = int(maxBrightness / 13.4);
//        int y = int(maxBrightness / 36.4);
//        int z = int(maxBrightness / 15);
//        
//        if (r_asc) {
//            rgb[0] += x;
//            if (rgb[0] > maxBrightness) {
//                rgb[0] = maxBrightness - (rgb[0] - maxBrightness);
//                r_asc = false;
//            }
//        }
//        else {
//            rgb[0] -= x;
//            if (rgb[0] < 0) {
//                rgb[0] = -1 * rgb[0];
//                r_asc = true;
//            }
//        }
//        
//        if (g_asc) {
//            rgb[1] += y;
//            if (rgb[1] > maxBrightness) {
//                rgb[1] = maxBrightness - (rgb[0] - maxBrightness);
//                g_asc = false;
//            }
//        }
//        else {
//            rgb[1] -= y;
//            if (rgb[1] < 0) {
//                rgb[1] = -1 * rgb[1];
//                g_asc = true;
//            }
//        }
//        
//        if (b_asc) {
//            rgb[2] += z;
//            if (rgb[2] > maxBrightness) {
//                rgb[2] = maxBrightness - (rgb[0] - maxBrightness);
//                b_asc = false;
//            }
//        }
//        else {
//            rgb[2] -= z;
//            if (rgb[2] < 0) {
//                rgb[2] = -1 * rgb[2];
//                b_asc = true;
//            }
//        }

      
      
//      if (r_asc) {
//        rgb[0] += x;
//        if (rgb[0] > 255) {
//          rgb[0] = 255;
//          r_asc = false;
//        }
//      }
//      else {
//        rgb[0] -= x;
//        if (rgb[0] < 0) {
//          rgb[0] = 0;
//          r_asc = true;
//        }
//      }
//    
//      if (g_asc) {
//        rgb[1] += y;
//        if (rgb[1] > 255) {
//          rgb[1] = 255;
//          g_asc = false;
//        }
//      }
//      else {
//        rgb[1] -= y;
//        if (rgb[1] < 0) {
//          rgb[1] = 0;
//          g_asc = true;
//        }
//      }
//    
//      if (b_asc) {
//        rgb[2] += z;
//        if (rgb[2] > 255) {
//          rgb[2] = 255;
//          b_asc = false;
//        }
//      }
//      else {
//        rgb[2] -= z;
//        if (rgb[2] < 0) {
//          rgb[2] = 0;
//          b_asc = true;
//        }
//      }
//    }
  }
  
  void adjust(char direction) {
    if (direction == 'l') {
      rate += 2;
    }
    else if (direction == 'r') {
      rate -= 2;
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
    
    void setMaxBrightness(int msx) {
        if (msx < 42){
            maxBrightness = 42;
        }
        else if (msx > 255) {
            maxBrightness = 255;
        }
        maxBrightness = msx;
    }
    
    int getRate() {
        return rate;
    }
    
    int getMaxBrightness() {
        return maxBrightness;
    }
};
