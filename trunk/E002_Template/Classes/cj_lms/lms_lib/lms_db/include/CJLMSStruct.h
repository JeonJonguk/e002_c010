//
//  CJLMSStruct.h
//  S001_Template
//
//  Created by Soonho Hong on 12. 10. 24..
//
//

#ifndef CJLMSStruct_h
#define CJLMSStruct_h

#include <sstream>
#include <vector>
#include <assert.h>
#include "sqlite3.h"

/**
 * @author CJEducations
 * @brief Struct for CJEducation LMS (add valriable iIdxKids, szImage in _KidsInfo)
 * @version v1.0.4
 * @date 2012. 11. 28
 * @since v1.0.0
 */

/**
 * @brief typedef struct
 */
typedef struct _KidsInfo        KidsInfo;
typedef struct _KidsContent     KidsContent;
typedef struct _Grade           Grade;
typedef struct _Progress        Progress;
typedef struct _ResFile         ResFile;
typedef struct _Content         Content;
typedef struct _Question        Question;

struct _KidsInfo {
    int             iPKGKidsId;         // PKGKids Id
    int             iIdxKids;           // Kids Id in Luncher
    int             iStage;             // Progressing Content Number
    int             iTotalStage;        // Total Content Number
    int             iUpdateId;
    std::string     szWriteDate;        // Write Date
    std::string     szCompleteDate;     // Complete Date
    std::string     szPKGCode;          // Package Code String Value
    std::string     szName;             // Kids Name
    std::string     szImage;            // Kids Image
    std::string     szBirth;            // Kids BirthDay
};

struct _KidsContent {
    int             iKidsContentId;     // KidsContent Id
    int             iKidsId;            // Kids Id
    int             iContentId;         // Content Id
    int             nCount;             // All Menu Study Count
    int             nGrade;             // Test Grade Number
    int             iUpdateId;          // Update to PlatForm's Server, Result Index (0-false/1-true)
    std::string     szStartDate;        // App install Date
    std::string     szEndDate;          // Recent Lunch App Date
    std::string     szKey;              // Auth Server Key Code
};

struct _Grade {
    int             iGradeId;           // Grade Id
    int             iKidsId;            // Kids Id
    int             iContentId;         // Content Id
    int             nGrade;             // Test Grade Number
    int             iUpdateId;          // Update to PlatForm's Server, Result Index (0-false/1-true)
    int             nQNum;		        // Question Number
    std::string     szWriteDate;        // Insert DB Date
    std::string     szKey;              // Auth Serve Key Code
    
    std::string     szExtra1;           // Etc String
};

struct _Progress {
    int             iProgressId;        // Progress Id
    int             iKidsId;            // Kids Id
    int             iContentId;         // Content Id
    int             iMenuNum;           // Content Menu Number Index
    int             nCount;             // Menu Study Count
    int             iUpdateId;          // Update to PlatForm's Server, Result Index (0-false/1-true)
    std::string     szStartDate;        // Menu Start Date
    std::string     szEndDate;          // Recent Play Menu Date
    std::string     szKey;              // Auth Server Key Code
};

struct _ResFile {
    int             iFileId;            // File Id
    int             idxKids;            // idxKids Id
    int             iContentId;         // Content Id
    int             iMenuNum;           // Content Menu Number
    int             iKind;              // Kind Index
    int             iGubun;             // Gubun Index (1-picture/2-sound)
    std::string     szWriteDate;        // Insert DB Date
    std::string     szPath;             // Resource Path Information
    std::string     szExtend1;
    std::string     szExtend2;
};

struct _Content{
    bool            bNull;              // Check Exist Data in Struct
    int             iContentId;         // Contetn Id
    int             iStage;             // Contetn Stage Number
    int             nMenuCount;         // Max Menu Number
    std::string     szPKGCode;          // Package App Index Name
    std::string     szContentCode;      // Content Index Name
    std::string     szTitle;            // Content Title
    std::string     szDescription;      // Content Description
    std::string     szGalleryTitle;     // Content Gallery Title
    std::string     szGalleryDesc;      // Content Gallery Description
};

struct _Question{
    int             iQuestionId;		// Question Id
    int             iQNum;				// Question Index Number
    int             iQCode;				// Question Type Code
    int             iMenuNum;			// Menu Number
    std::string     szContentCode;		// Content Index Name
    std::string     szThumbnailPath;	// Question Thumbnail Path
    std::string     szDesc;				// Question Description String
};

#endif
