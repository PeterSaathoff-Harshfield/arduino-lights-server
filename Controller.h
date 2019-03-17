#pragma once
// #include "Mode.h"
#include "Off.h"
#include "White.h"
#include "Spectrum.h"
#include "SolidColors.h"
#include "Gradient.h"
#include "Random.h"
#include "Flow.h"
#include "RedPulse.h"
#include "Arbitrary.h"

class Controller {
private:
  bool logging = true;
  
  Mode* modes[9];
  
  const int numberOfModes = sizeof(modes) / sizeof(modes[0]);
  int currentMode;
  int lastModeBeforeOff;
    
  int rgb[3];
  
  void putColors() {
    r = rgb[0];
    g = rgb[1];
    b = rgb[2];
  }
  
public:
  int r;
  int g;
  int b;
  
	Controller() {
	  r = 100;
      g = 100;
      b = 100;
    
    currentMode = 1;
    
    modes[0] = new Off();
    modes[1] = new White();
    modes[2] = new Spectrum();
    modes[3] = new SolidColors();
    modes[4] = new Gradient();
    modes[5] = new Random();
    modes[6] = new Flow();
    modes[7] = new RedPulse();
    modes[8] = new Arbitrary();
	}
  
    bool on() {
        if (currentMode != 0) {
            return true;
        }
        return false;
    }
    
    void powerToggle() {
        if (currentMode == 0) {
            currentMode = lastModeBeforeOff;
        }
        else { // if it is on
            lastModeBeforeOff = currentMode;
            currentMode = 0;
        }
    }
    
  void update(long now) {  
    modes[currentMode]->get(now, rgb);
    putColors();
  }
  
  void setMode(int modeIndex) {
    if (modeIndex >= 0 && modeIndex < numberOfModes) {
      currentMode = modeIndex;
    }
  }
  
  void switchMode(char direction) {
    if (direction == 'u') {
      currentMode += 1;
    }
    else if (direction == 'd') {
      currentMode -= 1;
    }

    int n = numberOfModes;
    if (currentMode < 0) {
      currentMode = n + currentMode;
    }
    else if (currentMode > 0) {
      currentMode = currentMode % n;
    }
    else {
      currentMode = 0;
    }
  
  }
  
  void adjustMode(char direction) {
    modes[currentMode]->adjust(direction);
  }
  
  void setWhite(int brightness) {
      modes[1]->setBrightness(brightness);
  }
    void setSolidColorMode(int color) {
        modes[3]->setColorMode(color);
    }
    void setRandomRate(int rate) {
        modes[5]->set(rate);
    }
    void setRandomMaxBrightness(int max) {
        modes[5]->setMaxBrightness(max);
    }
    void setSpectrumRate(int rate) {
        modes[2]->setRate(rate);
    }
    void setSpectrumBrightness(int spectrumBrightness) {
        modes[2]->setBrightness(spectrumBrightness);
    }
    void setGradientMode(int gradirnetMode) {
        modes[4]->setState(gradirnetMode);
    }
    void setFlowRate(int flowRate) {
        modes[6]->set(flowRate);
    }
    void setFlowMaxBrightness(int flowMax) {
        modes[6]->setMaxBrightness(flowMax);
    }
    void setGradientRate(int gradientRate) {
        modes[4]->setRate(gradientRate);
    }
    void setArbitraryR(int red) {
        modes[8]->setR(red);
    }
    void setArbitraryG(int green) {
        modes[8]->setG(green);
    }
    void setArbitraryB(int blue) {
        modes[8]->setB(blue);
    }
    
    void jsonState(char response[], int responseLength) {
        
        char* onString;
        char* powerButtonString;
        if (currentMode != 0) {
            onString = "On";
            powerButtonString = "Turn Off";
        }
        else {
            onString = "Off";
            powerButtonString = "Turn On";
        }
        
        
//        Serial.println(onString);
//        Serial.println(powerButtonString);
        

        snprintf(response, responseLength, "{\"powerStatus\": \"%s\", \"powerButtonText\": \"%s\", \"r\": %d, \"g\": %d, \"b\": %d, \"whiteBrightness\": %d, \"solidColor\": %d, \"randomRate\": %d, \"randomMaxBrightness\": %d, \"spectrumRate\": %d, \"spectrumBrightness\": %d, \"gradientState\": %d, \"gradientRate\": %d, \"flowRate\": %d, \"flowMaxBrightness\": %d}", onString, powerButtonString, r, g, b, modes[1]->getBrightness(), modes[3]->getColorMode(), modes[5]->getRate(), modes[5]->getMaxBrightness(), modes[2]->getRate(), modes[2]->getMaxBrightness(), modes[4]->getState(), modes[4]->getRate(), modes[6]->getRate(), modes[6]->getMaxBrightness());

    }
};

