

#ifndef log_h
#define log_h

#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "../SDL/src/core/android/SDL_android.h"
#include <android/log.h>
#include <jni.h>


void customLog(int t ,  char * fct,  char * description);



#endif /* log_h */