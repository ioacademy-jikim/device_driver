LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_CFLAGS    := -fPIE
LOCAL_LDFLAGS   := -fPIE -pie
LOCAL_MODULE    := myapp
LOCAL_SRC_FILES := input_app.c
include $(BUILD_EXECUTABLE)

