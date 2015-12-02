

#include "CustomLog.h"
/**
 *
 *Fonction de custom de logs
 */
void customLog(int t ,  char * fct,  char * description)
{
    //Définis dans CONSTANT.H
    if(DEBUG_MODE == 1)
    {
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
}