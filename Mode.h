#pragma once

class Mode {
public:
  
  Mode() {
    
  }
  
  virtual ~Mode() {}
  
    virtual void get(long now, int rgb[]) {}
  
  virtual void adjust(char direction) {}
    
    virtual void set(int level) {}
    
    virtual void setBrightness(int brightness) {}
    
    virtual void setColorMode(int color) {}
    
    virtual void setState(int state) {}
    
    virtual void setRate(int rate) {}
    
    virtual void setMaxBrightness(int max) {}
    
    virtual void setR(int r) {}
    virtual void setG(int g) {}
    virtual void setB(int b) {}
    virtual void setHue(int h) {}
    
    virtual int getBrightness() {}
    virtual int getColorMode() {}
    virtual void getColors(int colorArray[][3]) {}
    virtual int getRate() {}
    virtual int getMaxBrightness() {}
    virtual int getState() {}
};
