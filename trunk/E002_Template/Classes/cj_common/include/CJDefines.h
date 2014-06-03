//
//  CJDefines.h
//  CJTemplate
//
//  Created by Dongjin Park on 12. 10. 17..
//
//

#ifndef CJTemplate_CJDefines_h
#define CJTemplate_CJDefines_h

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CCNotificationCenter Observe Key
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CCTouch Priority on CJPopup menu
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define CJTOUCH_PRIORITY_POPUP      -129
#define CJTOUCH_PRIORITY_POPUPMENU  -130



///////////////////////////////////////////////////////////////
// NARRATION
///////////////////////////////////////////////////////////////
#define CJNOTIFICATION_VOICE_FINISHCALL                        "notification_sound_finishcall"
#define CJNOTIFICATION_VOICE_FINISHCALL2                        "notification_sound_finishcall2"

///////////////////////////////////////////////////////////////
// VIDEO
///////////////////////////////////////////////////////////////
#define CJNOTIFICATION_VIDEO_FINISHCALL                        "notification_video_finishcall"
#define CJNOTIFICATION_VIDEO_BUTTONCALL                        "notification_video_btncall"
#define CJNOTIFICATION_VIDEO_INDEX_BUTTONCALL                  "notification_video_index_btncall"
#define CJNOTIFICATION_FRAME_VIDEOVIEW_FINISHCALL              "notification_frame_videoview_finishcall"
///////////////////////////////////////////////////////////////
// CAMERA
///////////////////////////////////////////////////////////////
#define CJNOTIFICATION_PICTURE_FINISHCALL                        "notification_camera_picturefinishcall"
#define CJNOTIFICATION_VIDEO_RECORDING_FINISHCALL                "notification_video_recordingfinishcall"
#define CJNOTIFICATION_CAMERA_ONPAUSE_RECORDING_CALL            "notification_camera_onpause_recording_call"

///////////////////////////////////////////////////////////////
// VOICE RECORDING
///////////////////////////////////////////////////////////////
#define CJNOTIFICATION_VOICE_RECORDING_FINISHCALL                "notification_voice_recording_finishcall"
#define CJNOTIFICATION_RECORDED_VOICE_FINISHCALL                 "notification_recorded_voice_finishcall"
// Info Close
///////////////////////////////////////////////////////////////
#define CJNOTIFICATION_INFO_CLOSECALL                           "notification_info_closecall"
// Guide Close
///////////////////////////////////////////////////////////////
#define CJNOTIFICATION_GUIDE_CLOSECALL                           "notification_guide_closecall"
// Tip Close
///////////////////////////////////////////////////////////////
#define CJNOTIFICATION_TIP_CLOSECALL                            "notification_tip_closecall"

// Reward Popup Close
///////////////////////////////////////////////////////////////
#define CJNOTIFICATION_REWARD_ITEM_COMPLETE_CALL              "notification_item_popup_complete_Call"
#define CJNOTIFICATION_REWARD_POPUP_COMPLETE_CALL              "notification_reward_popup_complete_Call"

// MuteAlert Popup Close
///////////////////////////////////////////////////////////////
#define CJNOTIFICATION_MUTEALERT_CLOSECALL                      "notification_mutealert_closecall"

// MuteAlert Popup Skip
///////////////////////////////////////////////////////////////
#define CJNOTIFICATION_MUTEALERT_SKIPCALL                       "notification_mutealert_skipcall"

// MuteAlert Popup Volume Up
///////////////////////////////////////////////////////////////
#define CJNOTIFICATION_MUTEALERT_VOLUMEUPCALL                       "notification_mutealert_volumeupcall"



// LockAlert Popup Check
///////////////////////////////////////////////////////////////
#define CJNOTIFICATION_LOCKALERT_CHECKCALL                          "notification_lockalert_checkcall"

// PageEndAlert Popup Home
///////////////////////////////////////////////////////////////
#define CJNOTIFICATION_PAGEENDALERT_HOMECALL                        "notification_pageendalert_homecall"

// PageEndAlert Popup Replay
///////////////////////////////////////////////////////////////
#define CJNOTIFICATION_PAGEENDALERT_REPLAYCALL                      "notification_pageendalert_replaycall"

// PageEndAlert Popup Next
///////////////////////////////////////////////////////////////
#define CJNOTIFICATION_PAGEENDALERT_NEXTCALL                        "notification_pageendalert_nextcall"

// Camera CAllBack
#define kNotification_ClickedCancelAtImagePickerView                "kNotification_Camera_ClickedCancelAtImagePickerView"
#define kNotification_ClickedUseAtImagePickerView                   "kNotification_Camera_ClickedUseAtImagePickerView"
#define kNotification_DismissImagePickerView                        "kNotification_Camera_DismissImagePickerView"
#define kNotification_SaveAfterChangeMenu                           "kNotification_Camera_ChangeMenuView"
#define kNotification_SaveCameraImagePath                           "kNotification_Camera_SaveFilePath"
namespace VIDEOSTYLE
{
    enum VIDEOSTYLE
    {
        kFLAGADDBTNNOTOUCH = 0,
        kFLAGADDBTNTOUCHSKIP = 1,
        kFLAGADDBTNTOUCHPAUSE = 2,
        
        kFLAGNOTOUCH = 100,
        kFLAGTOUCHSKIP = 101,
        kFLAGTOUCHPAUSE = 102,
        
        
    };
}
#endif
