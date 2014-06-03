//
//  E002_LMSInterface.cpp
//  SoundPhonics_Step2
//
//  Created by j2enty on 2014. 4. 28..
//  Copyright (c) 2014년 CJ Educations. All rights reserved.
//

#include "E002_LMSInterface.h"
#include "CJLMSExtension.h"
#include "CJSaveDataInterface.h"

#include "CJUtils.h"
#include "CJLMSUtil.h"

using namespace LMSExtension;

static E002_LMSInterface *_sInterface = NULL;


//////////////////////////////////////////////////
// CJLMSInterface basic functions.
//////////////////////////////////////////////////
E002_LMSInterface* E002_LMSInterface::getInstance() {
    if(false == E002_LMSInterface::isExistInstance()) {
        _sInterface = new E002_LMSInterface();
    }
    
    return _sInterface;
}

void E002_LMSInterface::release() {
    if(true == E002_LMSInterface::isExistInstance()) {
        delete _sInterface;
        _sInterface = NULL;
    }
}

bool E002_LMSInterface::isExistInstance() {
    if(NULL!=_sInterface) {
        return true;
    } else {
        return false;
    }
}





//////////////////////////////////////////////////
// CJLMSInterface CONTENT OPERATION FUNCTIONS.
//////////////////////////////////////////////////


std::string E002_LMSInterface::getFileExtension(eFileType eFileType)
{
    switch(eFileType)
    {
        case eFileType_Image:
        case eFileType_Extend:
            return ".png";
            break;
        case eFileType_Sound:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            return ".caf";
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            return ".3gpp";
#endif
            break;
        case eFileType_Video:
            return ".mp4";
            break;
        default:
            break;
    }
}

bool E002_LMSInterface::deleteLMSFile(int iMenuID, eFileType eFileType)
{
    int resMaxCount = 0;
    if(eFileType_Video == eFileType)
        resMaxCount = 1;
    else if(eFileType_Image == eFileType)
        resMaxCount = 5;
    else if(eFileType_Extend == eFileType)
        resMaxCount = 1;
    
    std::vector<ResFile> *files = mFileInterface->getRemoveFiles(mDataStorage->getCurrentContentPrimaryKey(),
                                                                 eFileType,
                                                                 mDataStorage->getKidsInfo().iIdxKids,
                                                                 iMenuID);
    if(resMaxCount<=files->size())
    {
        for(int fileIdx=files->size(); fileIdx>=resMaxCount; fileIdx--)
        {
            std::string strDeleteFileName = files->at(fileIdx-1).szPath;
            std::string strDeleteExtendName = files->at(fileIdx-1).szExtend1;
            if(true == CJLMSExtension::sharedInstance()->removeSaveFile(strDeleteFileName.c_str()) &&
               true == CJLMSExtension::sharedInstance()->removeSaveFile(strDeleteExtendName.c_str())) {
                mFileInterface->removeFile(files->at(fileIdx-1));
            }
        }
    }
    
    delete files;
    
    return true;
}

std::string E002_LMSInterface::createLMSFile(int iMenuID, eFileType eFileType) {
    std::string strFileName;
    std::string strCurrentTime = this->getCurrentDate();
    std::stringstream strMenuValue;
    strMenuValue << iMenuID;
    std::stringstream strTypeValue;
    strTypeValue << eFileType;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    strFileName.append(mDataStorage->getDBPath());
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    strFileName.append(CJSaveDataInterface::sharedInstance()->getResourceDirPath(mDataStorage->getPKGCode().c_str()));
    strFileName.append("/");
#endif
    strFileName.append(CJLMSUtil::getPrepareKey(mDataStorage->getKidsInfo().iIdxKids,
                                                mDataStorage->getPKGCode(),
                                                mDataStorage->getCurrentContentCode(),
                                                FILE_KEY_CODE));
    
    strFileName.append(strMenuValue.str());
    strFileName.append("_");
    strFileName.append(strTypeValue.str());
    strFileName.append("_");
    strFileName.append(strCurrentTime);

//    strFileName.append(this->getFileExtension(eFileType));
    
    return strFileName;
}

std::string E002_LMSInterface::getLMSFileName(int iMenuID, eFileType eFileType,
                                              std::string strExtend1, std::string strExtend2) {
    if(true == this->isInit()) {
        if(40 <= iMenuID && 49 >= iMenuID) {
            this->deleteLMSFile(iMenuID, eFileType);
        } else {
            CJLMSInterface::deleteLMSFile(eFileType);
        }
        
        CJLMSExtension::sharedInstance()->checkStorageSize();
        
        std::string strFileName = this->createLMSFile(iMenuID, eFileType);
        std::string strFullFileName = strFileName;
        std::string strExpendFileName = strFileName;
        strFullFileName.append(this->getFileExtension(eFileType));
        
        
        ResFile resFile;
        resFile.idxKids     = mDataStorage->getKidsInfo().iIdxKids;
        resFile.iContentId  = mDataStorage->getCurrentContentPrimaryKey();
        resFile.szWriteDate = this->getCurrentDate();
        resFile.iMenuNum    = iMenuID;
        resFile.iGubun      = eFileType;
        resFile.szPath      = strFullFileName;
        
        if(40 <= iMenuID && 49 >= iMenuID) {
            std::string strBGName = strFileName;
            strBGName.append("_bg");
            strBGName.append(this->getFileExtension(eFileType));
            resFile.szPath = strBGName;
            
            std::string strCaptureName = strFileName;
            strCaptureName.append("_capture");
            strCaptureName.append(this->getFileExtension(eFileType));
            resFile.szExtend1 = strCaptureName;
            resFile.szExtend2 = strExtend1;
        }
        mFileInterface->setCurrentFile(resFile);
        
        
        if(40 <= iMenuID && 49 >= iMenuID) {
            return strFileName;
        } else {
            return strExpendFileName;
        }
    } else {
        return "";
    }
}

bool E002_LMSInterface::saveLMSFile() {
    return CJLMSInterface::saveLMSFile();
}

CJLMSResource E002_LMSInterface::getResFile(int iMenuID, eFileType eFileType) {
    ResFile resFile = mFileInterface->getResFile(mDataStorage->getCurrentContentPrimaryKey(),
                                                 eFileType,
                                                 mDataStorage->getKidsInfo().iIdxKids,
                                                 iMenuID);
    
    CJLMSResource resource;
    resource.menuID = resFile.iMenuNum;
    resource.szBGImageName = resFile.szPath;
    resource.szCaptureImageName = resFile.szExtend1;
    resource.szExtendData = resFile.szExtend2;
    
    return resource;
}










//////////////////////////////////////////////////
// CJLMS Recovery Interface CONTENT OPERATION FUNCTIONS.
//////////////////////////////////////////////////
bool E002_LMSInterface::recoveryStartPackage(int iTotalStage, std::string strPKGCode, int iIdxKids,
                                             std::string strStartDate, std::string strEndDate) {
    
}

bool E002_LMSInterface::recoveryEndPackage() {
    
}

bool E002_LMSInterface::recoveryStartContent(std::string strContentCode,
                                             std::string strStartDate, std::string strEndDate) {
    
}

bool E002_LMSInterface::recoveryEndContent() {
    
}

bool E002_LMSInterface::recoverySetContentProgress(int iMenuID, int iCount, std::string strKey,
                                                   std::string strStartDate, std::string strEndDate) {
    
}

bool E002_LMSInterface::recoverySetContentGrade(std::string strExtra, std::string strDate) {
    
}


