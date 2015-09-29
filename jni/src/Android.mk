LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL
MAIN_PATH := ..
USER_PATH := $(MAIN_PATH)/user

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
		$(LOCAL_PATH)/../SDL_ttf

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	$(USER_PATH)/shoot.c \
	$(USER_PATH)/userShip.c \
	$(MAIN_PATH)/main.c

LOCAL_SHARED_LIBRARIES :=  SDL2_ttf \
SDL2 


LOCAL_LDLIBS :=  -llog -lGLESv1_CM -lGLESv2 

include $(BUILD_SHARED_LIBRARY)
