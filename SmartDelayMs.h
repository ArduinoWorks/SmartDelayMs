#ifndef SMART_DELAY_MS_H
#define SMART_DELAY_MS_H

#if ARDUINO >= 100
 #include <Arduino.h>
#endif

#include "SmartDelay.h"

class SmartDelayMs: public SmartDelay {
  private:

  public:
    SmartDelayMs(){};
    SmartDelayMs(const SmartDelayMs& rhs);
    SmartDelayMs& operator= (const SmartDelayMs& rhs);
    SmartDelayMs(unsigned long tick) : SmartDelay(tick * 1000UL)

    unsigned long Set(unsigned long tick) {return SmartDelay::Set(tick * 1000UL); }
};

#define SMART_DELAY_MS_PROCESSES(name, ...) SmartDelayMS *name[]={__VA_ARGS__}
#define SMART_DELAY_MS_PROCCOUNT(name) (sizeof(name)/sizeof(SmartDelayMs*))
#define COOPTASKMS(name, ...) SMART_DELAY_MS_PROCESSES(Proc_Pointers_Ms_Array_name, __VA_ARGS__); coopTaskMs name(Proc_Pointers_Ms_Array_name, SMART_DELAY_MS_PROCCOUNT(Proc_Pointers_Ms_Array_name))

class coopTaskMs {
  private:
    SmartDelayMs **p;
    unsigned int count;
  public:
    coopTask() {};
    coopTask(SmartDelayMs **arr, unsigned int c) {
      p = arr;
      count=c;
    }
    void run() {
      for (int i = 0; i < count; i++) p[i]->run();
    }
};

#endif
