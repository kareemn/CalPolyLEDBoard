LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

include ../../sdk/native/jni/OpenCV.mk

LOCAL_MODULE    := native_sample
LOCAL_SRC_FILES := houghlines.cpp
LOCAL_LDLIBS +=  -llog -ldl

include $(BUILD_SHARED_LIBRARY)
