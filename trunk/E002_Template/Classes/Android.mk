LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := class_static

LOCAL_MODULE_FILENAME := libclass

dirs := $(shell find $(LOCAL_PATH) -type d)

cppfilestemp1 := $(shell find $(LOCAL_PATH) -type d)
cppfilestemp2 := $(shell find $(cppfilestemp1) -name *.cpp)
cppfilestemp3 := $(sort $(cppfilestemp2))
cppfiles := $(subst $(LOCAL_PATH)/,,$(cppfilestemp3))

LOCAL_SRC_FILES := $(cppfiles) \
	           cj_common/userDB/sqlite3.c\

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) 
			   
LOCAL_C_INCLUDES := $(dirs) \
                    $(LOCAL_PATH)/cj_common/multimedia \
                    $(LOCAL_PATH)/cj_common/utils \
                    $(LOCAL_PATH)/cj_common/userDB \
                    $(LOCAL_PATH)/cj_common/include \
                    $(LOCAL_PATH)/cj_common/framework \
                    $(LOCAL_PATH)/../libs/cocos2dx \
                    $(LOCAL_PATH)/../libs/cocos2dx/include \
                    $(LOCAL_PATH)/../libs/cocos2dx/kazmath/include \
                    $(LOCAL_PATH)/../libs/cocos2dx/platform \
                    $(LOCAL_PATH)/../libs/cocos2dx/platform/android \
                    $(LOCAL_PATH)/../libs/cocos2dx/platform/android/jni \
                    $(LOCAL_PATH)/../libs/CocosDenshion/include \
                    $(LOCAL_PATH)/../libs/extensions/GUI/CCScrollView \
                    $(LOCAL_PATH)/../libs/extensions \
                    $(LOCAL_PATH)/../libs/external/Box2D \
                    $(LOCAL_PATH)/../libs/external \
                    $(LOCAL_PATH)/../libs/CJPlatform/CJSaveData/include \
                    $(LOCAL_PATH)/../libs/CJPlatform/CJSound/include \
                    $(LOCAL_PATH)/../libs/CJPlatform/CJVideo/include \
                    $(LOCAL_PATH)/../libs/CJPlatform/CJCamera/include \
                    $(LOCAL_PATH)/../libs/CJPlatform/CJRecorder/include \
                    $(LOCAL_PATH)/../libs/CJPlatform/CJPSDParser \
                    $(LOCAL_PATH)/../libs/CJPlatform/CJParser \
                    $(LOCAL_PATH)/../libs/CJPlatform/CJAnimationLibrary \
                    $(LOCAL_PATH)/../libs/CJPlatform/CJAnimationLibrary/CJFlashAnimation \
                    $(LOCAL_PATH)/../libs/CJPlatform/CJAnimationLibrary/CJFlashBase \
                    $(LOCAL_PATH)/../libs/CJPlatform/CJAnimationLibrary/CJFlashExtensions \
                    $(LOCAL_PATH)/../libs/CJPlatform/CJAnimationLibrary/CJFlashUtil \
                    $(LOCAL_PATH)/../libs/CJPlatform/CJLMSExtension/include \
                    $(LOCAL_PATH)/../libs/CJPlatform/CJUriConnection/include


include $(BUILD_STATIC_LIBRARY)

 
