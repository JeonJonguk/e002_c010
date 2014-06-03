LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := CJSaveData_static

LOCAL_MODULE_FILENAME := libCJSaveData

LOCAL_SRC_FILES := CJSaveDataInterface.cpp \
		   jni/CJSaveDataInterfaceJni.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../include

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include \
                    $(LOCAL_PATH)/../../../cocos2dx \
                    $(LOCAL_PATH)/../../../cocos2dx/include \
                    $(LOCAL_PATH)/../../../cocos2dx/platform \
                    $(LOCAL_PATH)/../../../cocos2dx/platform/android \
                    $(LOCAL_PATH)/../../../cocos2dx/platform/android/jni

include $(BUILD_STATIC_LIBRARY)
