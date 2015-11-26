

#include "CustomLog.h"

void customLog(int t ,  char * fct,  char * description)
{
    //__android_log_print(ANDROID_LOG_DEBUG, "SpaceShip", "Android_JNI_GetAccelerometerValues");
   
    switch (t) {
        case 0:
            __android_log_print(ANDROID_LOG_DEBUG, fct,"%s",description);
            break;
            
        case 1:
            __android_log_print(ANDROID_LOG_DEBUG, fct,"%s",description);
            break;
            
        case 2:
            __android_log_print(ANDROID_LOG_DEBUG, fct,"%s",description);
            break;
            
        case 3:
            __android_log_print(ANDROID_LOG_DEBUG, fct,"%s",description);
            break;
        
           
        case 4:
            __android_log_print(ANDROID_LOG_DEBUG, fct,"%s",description);
            break;
        default:
            __android_log_print(ANDROID_LOG_DEBUG, fct,"%s",description);

            break;
    }
}