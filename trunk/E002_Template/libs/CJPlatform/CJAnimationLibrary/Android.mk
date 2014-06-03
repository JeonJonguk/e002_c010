LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := CJFlash_static

LOCAL_MODULE_FILENAME := libCJFlash

dirs := $(shell find $(LOCAL_PATH) -type d)

cppfilestemp1 := $(shell find $(LOCAL_PATH) -type d)
cppfilestemp2 := $(shell find $(cppfilestemp1) -name *.cpp)
cppfilestemp3 := $(sort $(cppfilestemp2))
cppfiles := $(subst $(LOCAL_PATH)/,,$(cppfilestemp3))

LOCAL_SRC_FILES := $(cppfiles)

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
			   
LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/CJFlashBase \
                    $(LOCAL_PATH)/CJFlashExtensions \
                    $(LOCAL_PATH)/CJFlashUtil \
                    $(LOCAL_PATH)/CJFlashAnimation \
                    $(LOCAL_PATH)/../CJParser \
                    $(LOCAL_PATH)/../../cocos2dx \
                    $(LOCAL_PATH)/../../cocos2dx/include \
                    $(LOCAL_PATH)/../../cocos2dx/platform \
                    $(LOCAL_PATH)/../../cocos2dx/platform/android \
                    $(LOCAL_PATH)/../../cocos2dx/platform/android/jni \
                    $(LOCAL_PATH)/../../cocos2dx/kazmath/include \
                    $(LOCAL_PATH)/../../CocosDenshion/include \
                    $(LOCAL_PATH)/../../../Classes/cj_common/include \
                    $(LOCAL_PATH)/../../../Classes/cj_common/utils \
                    $(LOCAL_PATH)/../../../Classes/cj_common/multimedia \
                    $(LOCAL_PATH)/../../../Classes/cj_common/framework \
                    $(LOCAL_PATH)/../../../Classes/cj_lms/lms_api

include $(BUILD_STATIC_LIBRARY)

 
