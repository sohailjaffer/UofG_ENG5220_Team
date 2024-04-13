#pragma once
#include <stdio.h>
#include "pigpio.h"
#include <iostream>
#include "unistd.h"
#include "pthread.h"
#include <cstring>


extern pthread_t thread2;

extern bool frontFlag;
extern bool backFlag;

void* SensorReset(void* arg);
void SensorCallback(int gpio);



class Main {
public:
   
private:

    
};


