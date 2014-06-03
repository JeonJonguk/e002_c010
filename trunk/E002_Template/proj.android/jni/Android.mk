LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp 
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes                   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static \
								cocosdenshion_static \
								cocos_extension_static \
								box2d_static \
								chipmunk_static \
								libwebsockets_static \
								CJLMSExtension_static \
								CJSound_static \
								CJVideo_static \
								CJCamera_static \
								CJSaveData_static \
								CJRecorder_static \
								CJPsdParser_static \
                             					CJParser_static \
								CJFlash_static \
								CJUri_static \
								class_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,CocosDenshion/android)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
$(call import-module,external/libwebsockets/android)
$(call import-module,extensions)
$(call import-module,CJPlatform/CJLMSExtension/android)
$(call import-module,CJPlatform/CJSound/android)
$(call import-module,CJPlatform/CJVideo/android)
$(call import-module,CJPlatform/CJCamera/android)
$(call import-module,CJPlatform/CJSaveData/android) 
$(call import-module,CJPlatform/CJRecorder/android)
$(call import-module,CJPlatform/CJUriConnection/android)
$(call import-module,CJPlatform/CJPSDParser)
$(call import-module,CJPlatform/CJParser)
$(call import-module,CJPlatform/CJAnimationLibrary)
$(call import-module,../Classes)
