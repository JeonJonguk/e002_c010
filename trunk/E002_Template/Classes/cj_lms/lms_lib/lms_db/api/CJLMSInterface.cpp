//
//  CJLMSInterface.cpp
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 23..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#include "CJLMSInterface.h"
#include "CJLMSExtension.h"
#include "CJUtils.h"
#include "CJLMSUtil.h"

#include "THResourceUtils.h"
#include "THFileUtil.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "CJSaveDataInterface.h"
#endif


using namespace LMSExtension;



//////////////////////////////////////////////////
//
// CJLMS_ContentInterface basic functions.
//
//////////////////////////////////////////////////
CJLMSInterface::CJLMSInterface()
{
    
}

CJLMSInterface::~CJLMSInterface()
{
    delete mPKGKidsInterface;
    delete mProgressInterface;
    delete mKidsContentInterface;
    delete mGradeInterface;
    delete mFileInterface;
    delete mContentInterface;
    delete mQuestionInterface;
    delete mDBManageInterface;
    delete mDataStorage;
    
    mPKGKidsInterface       = NULL;
    mProgressInterface      = NULL;
    mKidsContentInterface   = NULL;
    mGradeInterface         = NULL;
    mFileInterface          = NULL;
    mContentInterface       = NULL;
    mQuestionInterface      = NULL;
    mDBManageInterface      = NULL;
    mDataStorage            = NULL;
}

bool CJLMSInterface::init(std::string strDBPath)
{
    THResourceUtils::getCurrentUtils()->getData();
    CJLMSExtension::sharedInstance();
    mDataStorage                = CJLMSDataStorage::create();
    mDataStorage->setDBPath(strDBPath);
    mDataStorage->setDBConnectionTimeout(DEFAULT_DBCONN_TIMEOUT);
    mDBManageInterface          = CJLMS_DBManageInterface::create(mDataStorage);
    mPKGKidsInterface           = CJLMS_PKGKidsInterface::create(mDBManageInterface->getDBManager());
    mProgressInterface          = CJLMS_ProgressInterface::create(mDBManageInterface->getDBManager());
    mKidsContentInterface       = CJLMS_KidsContentInterface::create(mDBManageInterface->getDBManager());
    mGradeInterface             = CJLMS_GradeInterface::create(mDBManageInterface->getDBManager());
    mFileInterface              = CJLMS_FileInterface::create(mDBManageInterface->getDBManager());
    mContentInterface           = CJLMS_ContentInterface::create(mDBManageInterface->getDBManager());
    mQuestionInterface          = CJLMS_QuestionInterface::create(mDBManageInterface->getDBManager());

    return true;
}




//////////////////////////////////////////////////
//
// CJLMS_ContentInterface operating functions.
//
//////////////////////////////////////////////////
bool CJLMSInterface::isInit()
{
    
    CCLog("%d", mDataStorage->getCurrentStage());
    if(NULL==mDataStorage ||
       mDataStorage->getPKGCode().empty() ||
       mDataStorage->getCurrentContentPrimaryKey()<0 ||
       mDataStorage->getCurrentContentCode().empty() ||
       mDataStorage->getCurrentStage()<0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

std::string CJLMSInterface::getCurrentDate()
{
    return CJLMSExtension::sharedInstance()->getDeviceDateTime();
}

std::string CJLMSInterface::getCompateDate()
{
    return CJLMSExtension::sharedInstance()->getTargetDateTime(mDataStorage->getPKGID());
}

void CJLMSInterface::updateData()
{
    std::vector<KidsInfo>* kidsInfos = new std::vector<KidsInfo>();
    kidsInfos = mPKGKidsInterface->getPKGKidsForUpdate(mDataStorage->getKidsInfo().iIdxKids);
    
    if(0>=kidsInfos->size())
    {
        CCLog("---------------------------------------------------- NOT EXIST UPDATE DATA.");
        return ;
    }
    if(DB_ERROR == kidsInfos->at(0).iPKGKidsId)
    {
        CCLog("---------------------------------------------------- OCCER DB INIT ERROR");
    }
    
    CJLMSExtension::sharedInstance()->initLearnList();
    for(int kidsInfoIdx=0; kidsInfoIdx<kidsInfos->size(); kidsInfoIdx++)
    {
        CJLMSExtension::sharedInstance()->initContentList();
        
        CJLMSExtension::sharedInstance()->initLearn();
        CJLMSExtension::sharedInstance()->setLearnPKGName(kidsInfos->at(kidsInfoIdx).szPKGCode.c_str());
        CJLMSExtension::sharedInstance()->setLearnCompleteDate(kidsInfos->at(kidsInfoIdx).szCompleteDate.c_str());
        
        std::vector<KidsContent>* kidsContents = mKidsContentInterface->getKidsContentsForUpdate(kidsInfos->at(kidsInfoIdx).iPKGKidsId);
        for(int kidsContentIdx=0; kidsContentIdx<kidsContents->size(); kidsContentIdx++)
        {
            Content tempContent = mContentInterface->getContent(kidsContents->at(kidsContentIdx).iContentId);
            CCDictionary *tempDict = CCDictionary::create();
            tempDict->setObject(CCString::create(CONTENT_EXTRA_PACKAGE), CONTENT_EXTRA_KEY);
            
            CJLMSExtension::sharedInstance()->initStepList();
            CJLMSExtension::sharedInstance()->initGradeList();
            CJLMSExtension::sharedInstance()->initContent();
            
            CJLMSExtension::sharedInstance()->setContentCode(tempContent.szContentCode.c_str());
            CJLMSExtension::sharedInstance()->setContentExtra(CJLMSUtil::getJsonString(tempDict).c_str());

            std::vector<Progress>* progresses = mProgressInterface->getProgressesForUpdate(kidsInfos->at(kidsInfoIdx).iPKGKidsId,
                                                                                           kidsContents->at(kidsContentIdx).iContentId);
            for(int progressIdx=0; progressIdx<progresses->size(); progressIdx++)
            {
                Progress progress = progresses->at(progressIdx);
                
                std::string strMenuNum = "";
                std::stringstream streamMenuNum;
                streamMenuNum << progress.iMenuNum;
                strMenuNum.append(streamMenuNum.str());
                CCDictionary *tempDict = CCDictionary::create();
                tempDict->setObject(CCString::create(strMenuNum), STEP_EXTRA_KEY);
                
                
                CJLMSExtension::sharedInstance()->initStep();
                CJLMSExtension::sharedInstance()->setStepCount(progress.nCount);
                CJLMSExtension::sharedInstance()->setStepStartDate(progress.szStartDate.c_str());
                CJLMSExtension::sharedInstance()->setStepEndDate(progress.szEndDate.c_str());
                CJLMSExtension::sharedInstance()->setStepKey(progress.szKey.c_str());
                CJLMSExtension::sharedInstance()->setStepExtra(CJLMSUtil::getJsonString(tempDict).c_str());
                CJLMSExtension::sharedInstance()->addStep();
            }
            CJLMSExtension::sharedInstance()->setContentList();
            
            
            std::vector<Grade>*    grades     = mGradeInterface->getGradesForUpdate(kidsInfos->at(kidsInfoIdx).iPKGKidsId,
                                                                                    kidsContents->at(kidsContentIdx).iContentId);
            for(int gradeIdx=0; gradeIdx<grades->size(); gradeIdx++)
            {
                Grade grade = grades->at(gradeIdx);
                CJLMSExtension::sharedInstance()->initGrade();
                CJLMSExtension::sharedInstance()->setGrade(grade.nGrade);
                CJLMSExtension::sharedInstance()->setGradeDate(grade.szWriteDate.c_str());
                CJLMSExtension::sharedInstance()->setGradeExtra(grade.szExtra1.c_str());
                CJLMSExtension::sharedInstance()->addGrade();
            }
            CJLMSExtension::sharedInstance()->setContentGrade();
            
            CJLMSExtension::sharedInstance()->addContent();
            
            delete progresses;
            delete grades;
        }
        delete kidsContents;
        
        CJLMSExtension::sharedInstance()->setLearnList();
        CJLMSExtension::sharedInstance()->addLearn(mDataStorage->getKidsInfo().iIdxKids);
    }

    if(DB_SUCCESS == CJLMSExtension::sharedInstance()->sendLMSCenter())
    {
        for(int kidsInfoIdx=0; kidsInfoIdx<kidsInfos->size(); kidsInfoIdx++)
        {
            int kidsID = kidsInfos->at(kidsInfoIdx).iPKGKidsId;
            mPKGKidsInterface->setKidsUpdateID(kidsID, RECOVERY_SUCCESS);

            std::vector<KidsContent>* kidsContents = mKidsContentInterface->getKidsContentsForUpdate(kidsID);
            for(int kidsContentIdx=0; kidsContentIdx<kidsContents->size(); kidsContentIdx++)
            {
                int contentID = kidsContents->at(kidsContentIdx).iContentId;
                
                mKidsContentInterface->setKidsContentUpdateID(kidsID, contentID, RECOVERY_SUCCESS);

                std::vector<Progress>* progresses = mProgressInterface->getProgressesForUpdate(kidsID, contentID);
                for(int progressIdx=0; progressIdx<progresses->size(); progressIdx++)
                {
                    int menuID = progresses->at(progressIdx).iMenuNum;
                    
                    Progress progress = progresses->at(progressIdx);
                    mProgressInterface->setProgressUpdateID(kidsID, contentID, menuID, RECOVERY_SUCCESS);
                }
                
                std::vector<Grade>*    grades     = mGradeInterface->getGradesForUpdate(kidsID, contentID);
                for(int gradeIdx=0; gradeIdx<grades->size(); gradeIdx++)
                {
                    Grade grade = grades->at(gradeIdx);
                    mGradeInterface->setGradeUpdateID(grade.iGradeId, RECOVERY_SUCCESS);
                }
                
                delete progresses;
                delete grades;
            }
            delete kidsContents;
        }
    }
    else
    {
        // NOTHING.
    }
    
    delete kidsInfos;
}

bool CJLMSInterface::setContentKidsEndDate()
{
    if(false == this->isInit())
    {
        return false;
    }

    mPKGKidsInterface->setKidsUpdateID(mDataStorage->getKidsPrimaryKey(), RECOVERY_NEED);
    if(mKidsContentInterface->setKidsContentEndDate(mDataStorage->getKidsPrimaryKey(),
                                                    mDataStorage->getCurrentContentPrimaryKey(),
                                                    this->getCurrentDate()))
    {
        mKidsContentInterface->setKidsContentUpdateID(mDataStorage->getKidsPrimaryKey(),
                                                      mDataStorage->getCurrentContentPrimaryKey(),
                                                      RECOVERY_NEED);
        return true;
    }
    else
    {
        return false;
    }
}



//////////////////////////////////////////////////
// CJLMSInterface PAKCAGE OPERATION FUNCTIONS.
//////////////////////////////////////////////////
bool CJLMSInterface::isLauncherLogined()
{
    int childID = this->getKidsInfo().iIdxKids;
    
    return childID>0 ? true:false;
}

bool CJLMSInterface::startPackage(int iTotalStage, std::string strPKGCode)
{
    int idxKids;
    std::istringstream idStream(CJLMSExtension::sharedInstance()->getChildId());
    idStream >> idxKids;
    
    if(idxKids<0)
    {
        return false;
    }
    else
    {
        mDataStorage->setPKGCode(strPKGCode);
        
        KidsInfo kidsInfo;
        kidsInfo.iIdxKids           = idxKids;
        kidsInfo.iTotalStage        = iTotalStage;
        kidsInfo.szWriteDate        = this->getCurrentDate();
        kidsInfo.szCompleteDate     = this->getCompateDate();
        kidsInfo.szPKGCode          = strPKGCode;
        kidsInfo.szName             = CJLMSExtension::sharedInstance()->getChildName();
        kidsInfo.szBirth            = CJLMSExtension::sharedInstance()->getChildBirth();
        kidsInfo.szImage            = CJLMSExtension::sharedInstance()->getChildImage();
        mPKGKidsInterface->setKidsInfo(kidsInfo, idxKids);
        
        
        KidsInfo saveKidsInfo;
        saveKidsInfo            = mPKGKidsInterface->getPKGKidsInfo(idxKids, strPKGCode);
        saveKidsInfo.szName     = kidsInfo.szName;
        saveKidsInfo.szBirth    = kidsInfo.szBirth;
        saveKidsInfo.szImage    = kidsInfo.szImage;

        mDataStorage->setKidsInfo(saveKidsInfo);
        mDataStorage->setCurrentStage(saveKidsInfo.iStage);
        
        return true;
    }
}

bool CJLMSInterface::endPackage()
{
    return true;
}

bool CJLMSInterface::setContentResourcePraise(int iFileID, ePraiseType ePraiseType)
{
    return mFileInterface->setFilePraiseType(iFileID, ePraiseType);
}

int CJLMSInterface::getOpenStage()
{
    bool isOpenStage = CJUtils::getInstance()->getUserDefaultBoolForKey("PKG_isOpenStage");
	if(true == isOpenStage)
    {
		return mDataStorage->getCurrentStage();
	}
    else
    {
        CJUtils::getInstance()->setUserDefaultBoolForKey("PKG_isOpenStage", true);
        mDataStorage->setCurrentStage(1);
        
        return 1;
	}
}

bool CJLMSInterface::setOpenStage(int iStage)
{
    if(true == mPKGKidsInterface->setKidsStage(mDataStorage->getKidsPrimaryKey(), iStage))
    {
        mDataStorage->setCurrentStage(iStage);
        
        return true;
    }
    else
    {
        return false;
    }
}

int CJLMSInterface::getCurrentStage()
{
    return mDataStorage->getCurrentStage();
}

KidsInfo CJLMSInterface::getKidsInfo()
{
    return mDataStorage->getKidsInfo();
}

Content CJLMSInterface::getContent()
{
    return mContentInterface->getContent(mDataStorage->getCurrentContentPrimaryKey());
}

Content CJLMSInterface::getContent(int iStage)
{
    return mContentInterface->getContent(mDataStorage->getPKGCode(), iStage);
}

KidsContent CJLMSInterface::getKidsContent(int iContentPrimaryKey)
{
    return mKidsContentInterface->getKidsContent(mDataStorage->getKidsInfo().iPKGKidsId, iContentPrimaryKey);
}

std::vector<KidsContent>* CJLMSInterface::getKidsContents()
{
    return mKidsContentInterface->getKidsContents(mDataStorage->getKidsInfo().iPKGKidsId);
}

std::vector<Progress>* CJLMSInterface::getProgresses(int iContentPrimaryKey)
{
    return mProgressInterface->getProgresses(mDataStorage->getKidsInfo().iPKGKidsId, iContentPrimaryKey);
}

std::vector<Grade>* CJLMSInterface::getGrades(int iContentPrimaryKey)
{
    return mGradeInterface->getGrades(mDataStorage->getKidsInfo().iPKGKidsId, iContentPrimaryKey, 0);
}

std::vector<Grade>* CJLMSInterface::getGrades(int iContentPrimaryKey, int iQuestionPrimaryKey)
{
    return mGradeInterface->getGrades(mDataStorage->getKidsInfo().iPKGKidsId, iContentPrimaryKey, iQuestionPrimaryKey);
}

std::vector<ResFile>* CJLMSInterface::getContentResources(int iContentPrimaryKey, eFileType eFileType)
{
    return mFileInterface->getContentFiles(iContentPrimaryKey, eFileType, mDataStorage->getKidsInfo().iIdxKids);
}

std::vector<ResFile>* CJLMSInterface::getPackageResources(eFileType eFileType)
{
    return mFileInterface->getPackageFiles(eFileType, mDataStorage->getKidsInfo().iIdxKids);
}



//////////////////////////////////////////////////
// CJLMSInterface CONTENT OPERATION FUNCTIONS.
//////////////////////////////////////////////////
bool CJLMSInterface::startContent(std::string strContentCode)
{
    mDataStorage->setCurrentContent(mContentInterface->getContent(mDataStorage->getPKGCode(), strContentCode));
    
    KidsContent kidsContent;
    kidsContent.iKidsId     = mDataStorage->getKidsPrimaryKey();
    kidsContent.iContentId  = mDataStorage->getCurrentContentPrimaryKey();
    kidsContent.szStartDate = this->getCurrentDate();
    kidsContent.szEndDate   = this->getCurrentDate();
    kidsContent.szKey       = CJLMSUtil::getPrepareKey(mDataStorage->getKidsInfo().iIdxKids,
                                                       mDataStorage->getPKGCode(),
                                                       mDataStorage->getCurrentContentCode(),
                                                       KIDSCONTENT_KEY_CODE);
    
    return (mKidsContentInterface->setKidsContent(kidsContent, mDataStorage->getKidsPrimaryKey()));
}

bool CJLMSInterface::endContent()
{
    this->setContentKidsEndDate();
    this->updateData();
    
    Content nullContent;
    mDataStorage->setCurrentContent(nullContent);
    
    return true;
}

int CJLMSInterface::getKidsIdxKids()
{
    return mDataStorage->getKidsInfo().iIdxKids;
}

std::string CJLMSInterface::getResourceRootPath()
{
    return THFileUtil::getWriteablePath();
}

bool CJLMSInterface::setContentProgress(int iMenuID)
{
    if(false == this->isInit())
    {
        return false;
    }
    
	Content content = mContentInterface->getContent(mDataStorage->getCurrentContentPrimaryKey());
    
	Progress progress;
	progress.iKidsId        = mDataStorage->getKidsPrimaryKey();
	progress.iContentId     = mDataStorage->getCurrentContentPrimaryKey();;
	progress.iMenuNum       = iMenuID;
	progress.szStartDate    = this->getCurrentDate();
	progress.szEndDate      = this->getCurrentDate(); // insert db in progress table, because enddate set current date (default value)
	progress.szKey          = CJLMSUtil::getPrepareKey(mDataStorage->getKidsPrimaryKey(),
                                                       mDataStorage->getPKGCode(),
                                                       mDataStorage->getCurrentContentCode(),
                                                       PROGRESS_KEY_CODE);
    
    if(true == mProgressInterface->setProgress(progress, mDataStorage->getKidsPrimaryKey()))
    {
        mPKGKidsInterface->setKidsUpdateID(mDataStorage->getKidsPrimaryKey(),RECOVERY_NEED);
        mKidsContentInterface->setKidsContentUpdateID(mDataStorage->getKidsPrimaryKey(),
                                                      mDataStorage->getCurrentContentPrimaryKey(),
                                                      RECOVERY_NEED);
        mProgressInterface->setProgressCount(mDataStorage->getKidsPrimaryKey(),
                                             mDataStorage->getCurrentContentPrimaryKey(),
                                             iMenuID);

        std::vector<Progress>* progresses = mProgressInterface->getProgresses(mDataStorage->getKidsPrimaryKey(),
                                                                              mDataStorage->getCurrentContentPrimaryKey());

		int minProgress = 0;
		if (progresses->size() == content.nMenuCount)
        {
			minProgress = progresses->at(0).nCount;
			for (int progressIdx=1; progressIdx<progresses->size(); progressIdx++)
				minProgress < progresses->at(progressIdx).nCount ? minProgress : minProgress = progresses->at(progressIdx).nCount;
		}
        delete progresses;
        
		if (mKidsContentInterface->setKidsContentCount(mDataStorage->getKidsPrimaryKey(), mDataStorage->getCurrentContentPrimaryKey(),minProgress) &&
            true == this->setContentKidsEndDate())
        {
            
			int modifyContentId = mDataStorage->getCurrentContentPrimaryKey()+(mDataStorage->getCurrentContentPrimaryKey()-1)/4;
			if (minProgress >= 1 && modifyContentId == mDataStorage->getCurrentStage())
            {
                int stage = mDataStorage->getCurrentStage();
                
				if (stage == 4 || stage == 9 || stage == 14)
                {
					stage += 2;
				}
				else if (stage == 20)
                {
				}
                else
                {
					stage++;
				}
                
                if(true == mPKGKidsInterface->setKidsStage(mDataStorage->getKidsPrimaryKey(), stage))
                {
                    mDataStorage->setCurrentStage(stage);
                }
			}
            
			return true;
		}
        else
        {
			return false;
		}
	}
    else
    {
		return false;
	}
}

bool CJLMSInterface::setContentGrade(int iMenuID, int iPointValue, int iPointIndex)
{
    if(false == this->isInit())
    {
        return false;
    }
        
	Grade grade;
	grade.iKidsId       = mDataStorage->getKidsPrimaryKey();
	grade.iContentId    = mDataStorage->getCurrentContentPrimaryKey();
	grade.nGrade        = iPointValue;
    grade.nQNum         = mQuestionInterface->getQuestion(mDataStorage->getCurrentContentCode(), iMenuID, iPointIndex).iQuestionId;
	grade.szKey         = CJLMSUtil::getPrepareKey(mDataStorage->getKidsPrimaryKey(),
                                                   mDataStorage->getPKGCode(),
                                                   mDataStorage->getCurrentContentCode(),
                                                   GRADE_KEY_CODE);
	grade.szWriteDate   = getCurrentDate();
    
    if(true == mGradeInterface->setGrade(grade, mDataStorage->getKidsPrimaryKey()))
    {
        mKidsContentInterface->setKidsContentGrade(mDataStorage->getKidsPrimaryKey(),
                                                   mDataStorage->getCurrentContentPrimaryKey(),
                                                   iPointValue);
        mPKGKidsInterface->setKidsUpdateID(mDataStorage->getKidsPrimaryKey(), RECOVERY_NEED);
        mKidsContentInterface->setKidsContentUpdateID(mDataStorage->getKidsPrimaryKey(),
                                                      mDataStorage->getCurrentContentPrimaryKey(),
                                                      RECOVERY_NEED);
        
        return true;
    }
    else
    {
        return false;
    }
}


std::string CJLMSInterface::getSavedFileName(int iMenuID, eFileType eFileType)
{
    if(true == this->isInit())
    {
        return mFileInterface->getFilePath(mDataStorage->getCurrentContentPrimaryKey(),
                                           iMenuID,
                                           eFileType,
                                           mDataStorage->getKidsInfo().iIdxKids);
    }
    else
    {
        return false;
    }
}

std::string CJLMSInterface::getFileExtension(eFileType eFileType)
{
    switch(eFileType)
    {
        case eFileType_Image:
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
            return "";
            break;
    }
}

bool CJLMSInterface::deleteLMSFile(eFileType eFileType)
{
    int resMaxCount = 0;
    if(eFileType_Video == eFileType)
        resMaxCount = 1;
    else if(eFileType_Image == eFileType)
        resMaxCount = 5;
    
    std::vector<ResFile> *files = mFileInterface->getRemoveFiles(mDataStorage->getCurrentContentPrimaryKey(),
                                                                 eFileType,
                                                                 mDataStorage->getKidsInfo().iIdxKids);
    if(resMaxCount<=files->size())
    {
        for(int fileIdx=files->size(); fileIdx>=resMaxCount; fileIdx--)
        {
            std::string strDeleteFileName = files->at(fileIdx-1).szPath;
            if(true == CJLMSExtension::sharedInstance()->removeSaveFile(strDeleteFileName.c_str()))
            {
                mFileInterface->removeFile(files->at(fileIdx-1));
            }
        }
    }
    
    delete files;
    
    return true;
}

std::string CJLMSInterface::createLMSFile(int iMenuID, eFileType eFileType)
{
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
    strFileName.append(this->getFileExtension(eFileType));
    
    return strFileName;
}

std::string CJLMSInterface::getLMSFileName(int iMenuID, eFileType eFileType)
{
    if(true == this->isInit())
    {
        CJLMSExtension::sharedInstance()->checkStorageSize();
        
        this->deleteLMSFile(eFileType);
        std::string strFileName = this->createLMSFile(iMenuID, eFileType);
        
        ResFile resFile;
        resFile.idxKids     = mDataStorage->getKidsInfo().iIdxKids;
        resFile.iContentId  = mDataStorage->getCurrentContentPrimaryKey();
        resFile.iMenuNum    = iMenuID;
        resFile.iGubun      = eFileType;
        resFile.szPath      = strFileName;
        resFile.szWriteDate = this->getCurrentDate();
        mFileInterface->setCurrentFile(resFile);
        
        return strFileName;
    }
    else
    {
        return "";
    }
}

bool CJLMSInterface::saveLMSFile()
{
    if(true == this->isInit())
    {
        CJLMSExtension::sharedInstance()->checkStorageSize();
        
        return mFileInterface->saveCurrentFile();
    }
    else
    {
        return false;
    }
}
