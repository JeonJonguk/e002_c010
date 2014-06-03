/*
 *  CJUtils.cpp
 *
 *
 *  Created by Dongjin Park on 12. 10. 4..
 *  Copyright (c) 2012��__MyCompanyName__. All rights reserved.
 */



#include "CJUtils.h"
#include "CJUserContent.h"


USING_NS_CC;

#define MAX_LEN             (cocos2d::kMaxLogLen + 1)
#define TARGET_CENTER_X     512
#define TARGET_CENTER_Y     384

static CJUtils *m_spManagement;

CJUtils::CJUtils()
{
    m_rootPath = "";
    m_resourcePath = "";
    m_contentID = "";
    m_commonResourcePath = "";
    _bIsPopupStatus = false;
    m_language = "";
}

CJUtils::~CJUtils()
{
    releaseInstance();
}

CJUtils* CJUtils::getInstance()
{
    if(!m_spManagement)
    {
        m_spManagement  = new CJUtils();
        
    }
    return m_spManagement;
}

  
void CJUtils::releaseInstance()
{
    if (m_spManagement)
    {
        delete m_spManagement;
        m_spManagement = NULL;
    }
}
 
#pragma mark - contents controll.


void CJUtils::setRootPath(std::string tempPath)
{
    m_spManagement->m_rootPath = tempPath;
}

std::string CJUtils::getRootPath()
{
    return m_spManagement->m_rootPath;
}


void CJUtils::setContentID(std::string tempID)
{
    m_spManagement->m_contentID = tempID;
    std::string tempAppendedString = tempID.append("/");
//    m_spManagement->m_commonResourcePath = tempAppendedString;
    m_spManagement->m_resourcePath = tempAppendedString;
}

std::string CJUtils::getContentID()
{
    return m_spManagement->m_contentID;
}


std::string CJUtils::getResourcePath()
{
    std::string resourcePath = m_spManagement->getRootPath().append( m_spManagement->m_resourcePath );
    return resourcePath;
}

void CJUtils::setCommonResourcePath(std::string commonPath)
{
    m_spManagement->m_commonResourcePath = commonPath.append("/");
}

std::string CJUtils::getCommonResourcePath()
{
    std::string resourcePath = m_spManagement->m_commonResourcePath;
    return resourcePath;
}

int CJUtils::getKidId()
{
    return 0; //temp
//    return CJLMSContentInterface::getInstance()->getKidsIdx();
}

std::string CJUtils::getFontPath()
{
//    std::string strLabelFont = CJUtils::getInstance()->getCommonRootPath();
//    strLabelFont.append("/fonts/RixGoM.ttf");
//    return strLabelFont;
    return "";
}

void CJUtils::setLanguage(std::string language)
{
    m_language = language;
}

std::string CJUtils::getLanguage()
{
    return m_language;
}

#pragma mark - userdefault

void CJUtils::setUserDefaultBoolForKey(std::string pKey , bool value)
{
    //appen kid id.
    int kidId = getKidId();
    stringstream str;
    str<<kidId;
    string key = str.str();
    key = key.append(pKey);
    
    
    std::string tempValue = CJUserContent::sharedInstance()->selectContent(key);
    std::stringstream c_str ;
    c_str << value;
    std::string tempData = c_str.str();
    
    if(!tempValue.compare("default"))
        CJUserContent::sharedInstance()->insertFile(key, tempData);
    else
        CJUserContent::sharedInstance()->updateFile(key, tempData);
}

void CJUtils::setUserDefaultIntegerForKey(std::string pKey , int value)
{
    //appen kid id.
    int kidId = getKidId();
    stringstream str;
    str<<kidId;
    string key = str.str();
    key = key.append(pKey);
    
    
    std::string tempValue = CJUserContent::sharedInstance()->selectContent(key);
    std::stringstream c_str ;
    c_str << value;
    std::string tempData = c_str.str();
    
    if(!tempValue.compare("default"))
        CJUserContent::sharedInstance()->insertFile(key, tempData);
    else
        CJUserContent::sharedInstance()->updateFile(key, tempData);
}

void CJUtils::setUserDefaultFloatForKey(std::string pKey , float value)
{
    //appen kid id.
    int kidId = getKidId();
    stringstream str;
    str<<kidId;
    string key = str.str();
    key = key.append(pKey);
    
    std::string tempValue = CJUserContent::sharedInstance()->selectContent(key);
    
    std::stringstream c_str ;
    c_str << value;
    std::string tempData = c_str.str();
    
    if(!tempValue.compare("default"))
        CJUserContent::sharedInstance()->insertFile(key, tempData);
    else
        CJUserContent::sharedInstance()->updateFile(key, tempData);
    
}

void CJUtils::setUserDefaultStringForKey(std::string pKey , std::string value)
{
    //appen kid id.
    int kidId = getKidId();
    stringstream str;
    str<<kidId;
    string key = str.str();
    key = key.append(pKey);
    
    std::string tempValue = CJUserContent::sharedInstance()->selectContent(key);
    
    if(!tempValue.compare("default"))
        CJUserContent::sharedInstance()->insertFile(key, value);
    else
        CJUserContent::sharedInstance()->updateFile(key, value);
}

void CJUtils::setUserDefaultDoubleForKey(std::string pKey , double value)
{
    //appen kid id.
    int kidId = getKidId();
    stringstream str;
    str<<kidId;
    string key = str.str();
    key = key.append(pKey);
    
    std::string tempValue = CJUserContent::sharedInstance()->selectContent(key);
    
    std::stringstream c_str ;
    c_str << value;
    std::string tempData = c_str.str();
    
    if(!tempValue.compare("default"))
        CJUserContent::sharedInstance()->insertFile(key, tempData);
    else
        CJUserContent::sharedInstance()->updateFile(key, tempData);
}


bool CJUtils::getUserDefaultBoolForKey(std::string pKey)
{
    //appen kid id.
    int kidId = getKidId();
    stringstream str;
    str<<kidId;
    string key = str.str();
    key = key.append(pKey);
    
    std::string tempValue = CJUserContent::sharedInstance()->selectContent(key);
    bool retValue = false;
    if(!tempValue.compare("default"))
        retValue = false;
    else
    {
        istringstream(tempValue) >> retValue;
    }
    
    return retValue;
}

int CJUtils::getUserDefaultIntegerForKey(std::string pKey)
{
    
    //appen kid id.
    int kidId = getKidId();
    stringstream str;
    str<<kidId;
    string key = str.str();
    key = key.append(pKey);
    
    std::string tempValue = CJUserContent::sharedInstance()->selectContent(key);
    int retValue = 0 ;
    
    if(!tempValue.compare("default"))
        retValue = 0;
    else
    {
        std::istringstream buffer(tempValue);
        buffer>>retValue;
    }
    return retValue;
}

float CJUtils::getUserDefaultFloatForKey(std::string pKey)
{
    //appen kid id.
    int kidId = getKidId();
    stringstream str;
    str<<kidId;
    string key = str.str();
    key = key.append(pKey);
    
    
    std::string tempValue = CJUserContent::sharedInstance()->selectContent(key);
    float retValue = 0.0f;
    
    if(!tempValue.compare("default"))
        retValue = 0;
    else
    {
        std::istringstream buffer(tempValue);
        buffer>>retValue;
    }
    return retValue;
}

std::string CJUtils::getUserDefaultStringForKey(std::string pKey)
{
    //appen kid id.
    int kidId = getKidId();
    stringstream str;
    str<<kidId;
    string key = str.str();
    key = key.append(pKey);
    
    std::string tempValue = CJUserContent::sharedInstance()->selectContent(key);
    std::string retValue("");
    if(!tempValue.compare("default"))
        retValue = "";
    else
        retValue = tempValue;
    
    return retValue;
}

double CJUtils::getUserDefaultDoubleForKey(std::string pKey)
{
    
    //appen kid id.
    int kidId = getKidId();
    stringstream str;
    str<<kidId;
    string key = str.str();
    key = key.append(pKey);
    
    std::string tempValue = CJUserContent::sharedInstance()->selectContent(key);
    double retValue = 0;
    
    if(!tempValue.compare("default"))
        retValue = 0;
    else
    {
        std::istringstream buffer(tempValue);
        buffer>>retValue;
    }
    return retValue;
}



#pragma mark - getFilePath
std::string CJUtils::addContentIDPrefix(std::string strTemp)
{
    std::string result = getContentID().append(strTemp);
    return result;
}


std::string CJUtils::getFilePath(std::string strFolderName, std::string strFileName, bool isDiffentLanguage)
{
    std::string result = m_spManagement->m_resourcePath;
    result.append(strFolderName);
    result.append("/");
    
    if(isDiffentLanguage)
    {
        result.append(getLanguage());
        result.append("/");
    }
    
    result.append(strFileName);
    return result;
}

std::string CJUtils::getFilePath(std::string strFileName)
{
    std::string result = m_spManagement->getResourcePath();
    result.append(strFileName);
    return result;
}

std::string CJUtils::getCommonFilePath(std::string strFileName)
{

    std::string result = m_spManagement->getCommonResourcePath();
    result.append(strFileName);
    return result;

}

std::string CJUtils::getCommonFilePath(std::string strFolderName, std::string strFileName)
{
    
    std::string result = m_spManagement->getCommonResourcePath();
    result.append(strFolderName);
    result.append("/");
    result.append(strFileName);
    return result;
    
}

//CCSprite* CJUtils::setSpriteInstance(std::string strPath , std::string strRes , std::string strFileName , CCDictionary  *tempArray )
//{
//    
//    CCString * positionString = new CCString(*tempArray->valueForKey(strFileName.c_str()));
//    
//    std::string stdString = positionString->getCString();
//    
//    delete positionString;
//    char _key[500];
//    char* result = NULL;
//    
//    std::string strImgName;
//    float yPos = 200.0f;
//    float xPos = 200.0f;
//    
//    if(stdString.size()>0)
//    {
//        strcpy(_key, stdString.c_str());
//        
//        result = strtok((char*)_key, "/");
//        
//        yPos= (float)atof(result);
//        
//        result = strtok(NULL, "/");
//        
//        xPos = (float)atof(result);
//        
//        result = strtok(NULL, "/");
//        
//        strImgName = result;
//    }
//    
//    std::string imgFullPath = m_spManagement->getFilePath(strPath, strRes, strImgName).c_str();
//    std::string tempName;
//    
//    if (strchr(strImgName.c_str(),'@')!= NULL)
//    {
//        tempName = strtok((char*)imgFullPath.c_str(), "@");
//    }
//    else
//    {
//        tempName = imgFullPath.substr(0, imgFullPath.size()-4);
//    }
//    
//    std::string addPng = tempName;
//    addPng.append(".png");
//    imgFullPath = addPng;
//    
//    CCSprite *xmlSprite = CCSprite::create(imgFullPath.c_str());
//    
//    if (xmlSprite == NULL) {
//        
//        CCLog("png file is null!");
//        
//        std::string delPng = imgFullPath.substr(0, imgFullPath.size()-4);
//        
//        std::string addJpg = delPng;
//        addJpg.append(".jpg");
//        
//        xmlSprite = CCSprite::create(addJpg.c_str());
//        
//        // error
//        if (xmlSprite == NULL) {
//            CCLog("no Image :'%s'",delPng.c_str());
//            CC_ASSERT( xmlSprite != NULL);
//        }
//    }
//    xmlSprite->setPosition(ccp(xPos, yPos));
//    
//    // remove buffer
//    memset(_key, 0, sizeof(_key));
//    
//    return xmlSprite;
//}


//CCPoint CJUtils::getSpritePosition(std::string strFileName , CCDictionary *tempArray)
//{
//    CCString * positionString = new CCString(*tempArray->valueForKey(strFileName.c_str()));
//    
//    std::string stdString = positionString->getCString();
//    
//    delete positionString;
//    
//    char _key[500];
//    strcpy(_key, stdString.c_str());
//    
//    char* result = NULL;
//    
//    result = strtok((char*)_key, "/");
//    
//    float yPos = (float)atof(result);
//    
//    result = strtok(NULL, "/");
//    
//    float xPos = (float)atof(result);
//    CCPoint tempPoint = ccp(xPos,yPos);
//    
//    memset(_key, 0, sizeof(_key));
//    
//    return tempPoint;
//}

#pragma mark - LMS control
// Lms control
//void CJUtils::setLmsStart(std::string menuStr)
//{
//}
//void CJUtils::setLmsEnd()
//{
//}

void CJUtils::setLmsMenuEnd(int iMenuValue)
{
    CJLMSContentInterface::getInstance()->setLMSMenuEnd(iMenuValue);
}

std::string CJUtils::getLMSFileName(int iMenuID, eFileType eFileType,
                                    std::string strExtend1/* = ""*/, std::string strExtend2/* = ""*/)
{
    return CJLMSContentInterface::getInstance()->getLMSFileName(iMenuID, eFileType, strExtend1, strExtend2);
}

bool CJUtils::saveLMSFile()
{
    return CJLMSContentInterface::getInstance()->saveLMSFile();
}

#pragma mark - memory controll

void CJUtils::removeAllchildren(CCNode *node)
{
    if (node == NULL)
        return;
    
    node->stopAllActions();
    node->unscheduleUpdate();
    node->unscheduleAllSelectors();
    
    if (node->getChildren() > 0)
    {
        for (int i=0; i < ((CCArray*)node->getChildren())->count(); i++)
        {
            CCNode* child =  (CCNode*)((CCArray*)node->getChildren())->objectAtIndex(i);
            
            if (child->getChildrenCount() != 0)
            {
                removeAllchildren(child);
            }
        }
    }
    
    node->removeAllChildrenWithCleanup(true);

    
}

#pragma mark - action controll

void CJUtils::stopAllAnimations(CCNode *node)
{
    node->stopAllActions();
    
    if ((CCArray*)node->getChildren() == NULL) {
        return;
    }
    
    for (int i=0; i < ((CCArray*)node->getChildren())->count(); i++)
    {
        CCNode* child =  (CCNode*)((CCArray*)node->getChildren())->objectAtIndex(i);
        
        if (child->getChildrenCount() != 0)
        {
            stopAllAnimations(child);
        }
        else
        {
            child->stopAllActions();
        }
    }
}

void CJUtils::pauseAllAnimations(CCNode *node)
{
    node->pauseSchedulerAndActions();
    
    for (int i=0; i < ((CCArray*)node->getChildren())->count(); i++)
    {
        CCNode* child =  (CCNode*)((CCArray*)node->getChildren())->objectAtIndex(i);
        
        if (child->getChildrenCount() != 0)
        {
            pauseAllAnimations(child);
        }
        else
        {
            child->pauseSchedulerAndActions();
        }
    }
}


void CJUtils::resumeAllAnimations(CCNode *node)
{
    node->resumeSchedulerAndActions();
    
    for (int i=0; i < ((CCArray*)node->getChildren())->count(); i++)
    {
        CCNode* child =  (CCNode*)((CCArray*)node->getChildren())->objectAtIndex(i);
        
        if (child->getChildrenCount() != 0)
        {
            resumeAllAnimations(child);
        }
        else
        {
            child->resumeSchedulerAndActions();
        }
    }
}


void CJUtils::enterBackground()
{
    //CJPlatformBridge::sharedPlatformBridge()->pauseVideo();
    
    if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    {
        //CJPlatformBridge::sharedPlatformBridge()->pauseAllSounds();
    }
}

void CJUtils::enterForeground()
{
    //CJPlatformBridge::sharedPlatformBridge()->resumeVideo();
    
    if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    {
        //CJPlatformBridge::sharedPlatformBridge()->resumeAllSounds();
    }
}


#pragma mark - touch

bool CJUtils::hitTestPoint(CCNode* pNode, const CCPoint& pos, bool bCenter)
{
    CCPoint local = pNode->convertToNodeSpace(pos);
    CCRect r = CJUtils::rect(pNode);
    r.origin = CCPointZero;
    if (r.containsPoint( local))
    {
        if (bCenter == true)
        {
            float moveX = local.x - r.size.width/2;
            float moveY = local.y - r.size.height/2;
            
            pNode->setPosition(ccp(pNode->getPosition().x+moveX, pNode->getPosition().y+moveY));
        }
        return true;
    }
    
    return false;
}

bool CJUtils::hitTestObjects(CCNode* pNode1, CCNode* pNode2)
{
    CCPoint node2worldPos = pNode2->convertToWorldSpace(CCPointZero);
    
    CCPoint node2local = pNode1->convertToNodeSpace(node2worldPos);
    
    CCRect r1 = CJUtils::rect(pNode1);
    r1.origin = CCPointZero;
    
    CCRect r2 = CJUtils::rect(pNode2);
    r2.origin = node2local;
    
    if (r1.intersectsRect(r2))
    {
        return true;
    }
    
    return false;
}



bool CJUtils::containRect(CCLayer* layer, CCNode* node, CCPoint touch)
{
    if (node == NULL) return false;
    
    float posx = node->getPosition().x;
    float posy = node->getPosition().y;
    
    CCSize size = CCSizeMake(node->boundingBox().size.width, node->boundingBox().size.height);
    CCPoint anchor = node->getAnchorPoint();
    
    float anchorWidth = posx - (size.width * anchor.x);
    float anchorHeight = posy - (size.height * anchor.y);
    
    
    CCPoint modifyPoint = CCPointMake(anchorWidth, anchorHeight);
    CCRect modifyRect = CCRectMake(modifyPoint.x, modifyPoint.y, size.width, size.height);
    
    float s = sinf(node->getRotation()*(M_PI/180));
    float c = cosf(node->getRotation()*(M_PI/180));
    
    CCPoint modifyTouch = ccp(posx + ((touch.x - posx)*c - (touch.y-posy)*s),
                              posy + ((touch.x - posx)*s + (touch.y-posy)*c));
    
    return modifyRect.containsPoint(modifyTouch);
}

bool CJUtils::containRect(CCLayer* layer, CCNode* node, CCPoint touch, float band)
{
	float x = node->getPosition().x;
	float y = node->getPosition().y;
    
	CCSize size = node->boundingBox().size;
	CCPoint anchor = node->getAnchorPoint();
    
	float anchorWidth = x-((size.width+band)*anchor.x);
	float anchorHeight = y-((size.height+band)*anchor.y);
    
	CCPoint modifyPoint = CCPointMake(anchorWidth
                                      , anchorHeight);
	CCRect modifyRect = CCRectMake(modifyPoint.x
                                   , modifyPoint.y, size.width+band, size.height+band);
    
	float s = sinf(node->getRotation()*(M_PI/180));
	float c = cosf(node->getRotation()*(M_PI/180));
    
	CCPoint modifyTouch = ccp(x+((touch.x-x)*c-(touch.y-y)*s)
                              , y+((touch.x-x)*s+(touch.y-y)*c));
    
	return modifyRect.containsPoint(modifyTouch);
}

bool CJUtils::containPointWithBand(CCPoint targetPoint, CCPoint touch, float bandSize)
{
    
	float x = targetPoint.x;
	float y = targetPoint.y;
    
	CCPoint modifyPoint = CCPointMake(x-bandSize/2 , y-bandSize/2);
	CCRect modifyRect = CCRectMake(modifyPoint.x, modifyPoint.y, bandSize, bandSize);
    
    //CCLayerColor* layer1 = CCLayerColor::layerWithColorWidthHeight(ccc4f(50,200,50,0), bandSize, bandSize);
    //layer1->setPosition(modifyPoint);
    //layer->addChild(layer1,100);
    
	return modifyRect.containsPoint(touch);
}



CCRect CJUtils::rect(CCNode* pNode)
{
    return CCRectMake(pNode->getPosition().x - pNode->getContentSize().width * pNode->getAnchorPoint().x,
                      pNode->getPosition().y - pNode->getContentSize().height * pNode->getAnchorPoint().y,
                      pNode->getContentSize().width,
                      pNode->getContentSize().height);
}


#pragma mark - edit string 

std::string CJUtils::getStringMerge(std::string str1, std::string str2)
{
    std::string tempStr;
    tempStr.clear();
    
    tempStr.append(str1);
    tempStr.append(str2);
    
    return tempStr;
}

std::string CJUtils::getStringMerge(std::string str1, int nNumber)
{
    std::string tempStr;
    std::stringstream tempStream;
    
    tempStr.clear();
    tempStream.clear();
    
    tempStream << nNumber;
    
    tempStr.append(str1);
    tempStr.append(tempStream.str());
    
    return tempStr;
}

std::string CJUtils::getStringMerge(std::string str1, int nNumber, std::string str2)
{
    std::string tempStr;
    std::stringstream tempStream;
    
    tempStr.clear();
    tempStream.clear();
    
    tempStream << nNumber;
    
    tempStr.append(str1);
    tempStr.append(tempStream.str());
    tempStr.append(str2);
    
    return tempStr;
}


std::string CJUtils::getStringFormatInteger(std::string format, int nInteger)
{
    return cocos2d::CCString::createWithFormat(format.c_str(), nInteger)->getCString();
}

std::string CJUtils::getStringFormatString(std::string format, std::string str)
{
    return cocos2d::CCString::createWithFormat(format.c_str(), str.c_str())->getCString();
}


std::string CJUtils::stringTokenizer(std::string sentence, std::string tok, bool first)
{
    std::string tempStr = sentence;
    
    int start, stop, n = tempStr.length();
    
    for(start = tempStr.find_first_not_of(tok); 0 <= start && start < n; start = tempStr.find_first_not_of(tok, stop + 1))
    {
        stop = tempStr.find_first_of(tok, start);
        
        if (stop < 0 || stop > n)
            stop = n;
        
        if (first)
        {
            return tempStr.substr(start, stop - start);
        }
        else if (stop == n)
        {
            return tempStr.substr(start, stop - start);
        }
    }
    
    return "error";
}

std::string CJUtils::stringTokenizer(std::string sentence, std::string tok, int index)
{
    std::string tempStr = sentence;
    int i = 1;
    
    int start, stop, n = tempStr.length();
    
    for(start = tempStr.find_first_not_of(tok);
        0 <= start && start < n;
        start = tempStr.find_first_not_of(tok, stop + 1))
    {
        stop = tempStr.find_first_of(tok, start);
        if (stop < 0 || stop > n) stop = n;
        
        if (i == index)
        {
            return tempStr.substr(start, stop - start);
        }
        i++;
    }
    
    return "error";
}

#pragma mark - position & anchorPoint Function

void CJUtils::setPositionForParent(CCNode* parent, CCNode* child)
{
	CCSize parentSize = parent->getContentSize();
	CCPoint parentAnchor = parent->getAnchorPoint();
	CCPoint childModifyPoint = ccpSub(child->getPosition(), parent->getPosition());
	child->setPosition(
                       ccp(
                           childModifyPoint.x+parentSize.width*parentAnchor.x,
                           childModifyPoint.y+parentSize.height*parentAnchor.y
                           )
                       );
}

void CJUtils::setAnchorPointForPosition(CCNode* node, CCPoint anchor)
{
    CCSize size = node->getContentSize();
    CCPoint position = node->getPosition();
    CCPoint originAnchor = node->getAnchorPoint();
    
    node->setPosition(ccp(position.x-(size.width*(originAnchor.x-anchor.x)), position.y-(size.height*(originAnchor.y-anchor.y))));
    node->setAnchorPoint(anchor);
}

void CJUtils::setTransformCenterPosition(CCNode* node, CCPoint center)
{
    CCPoint originPoint = node->getPosition();
    
    node->setPosition(ccp(center.x-(TARGET_CENTER_X-originPoint.x), center.y-(TARGET_CENTER_Y-originPoint.y)));
}

CCPoint CJUtils::getTransformCenterPoint(CCPoint origin, CCPoint center)
{
    return ccp(center.x-(TARGET_CENTER_X-origin.x), center.y-(TARGET_CENTER_Y-origin.y));
}

#pragma mark - random Function
float CJUtils::randomFloat(float low, float hi)
{
    float r = (float)(std::rand() & 32767);
    r /= 32767;
    r = (hi - low) * r + low;
    return r;
}

/*  randomInteger(0,5) = {0,1,2,3,4,5} */
int CJUtils::randomInteger(int low, int hi)
{
    int r = arc4random() % (hi+1 - low) + low;
    return r;
}

int CJUtils::randomIntegerWithoutValue(unsigned int nMax, unsigned int nWithoutValue)
{
    int randValue = 0;
    
    do{
        randValue = arc4random()%nMax+1;
    }while(randValue == nWithoutValue);
    
    return randValue;
}

bool CJUtils::randomBoolean()
{
    return arc4random()%2 == 1 ? true : false;
}

float CJUtils::roundValue(float value, int pos)
{
    float temp;
    
    temp = value*pow(10, pos);
    temp = floor(temp+0.5);
    temp *= pow(10, -pos);
    
    return temp;
}


int* CJUtils::randomIntegerArr(const unsigned nMax)
{
    int count = nMax;
    int *array = new int[nMax];
    
    for(int i=0; i<nMax; i++)
    {
        array[i] = i;
    }
    for(int i=0; i<nMax; i++)
    {
        std::swap(array[arc4random()%count], array[--count]);
    }
    
    return array;
}

#pragma mark - performSelector

void CJUtils::performSelector(cocos2d::CCObject *pTarget,
                                        cocos2d::SEL_CallFunc aSelector,
                                        float afterDelay,
                                        int tag)
{
    cocos2d::CCFiniteTimeAction *performSeq = cocos2d::CCSequence::create(cocos2d::CCDelayTime::create(afterDelay),
                                                                          cocos2d::CCCallFunc::create(pTarget, aSelector), NULL);
    performSeq->setTag(tag);
    
    ((cocos2d::CCNode *)pTarget)->runAction(performSeq);
}

void CJUtils::performSelector(cocos2d::CCObject *pTarget,
                                        cocos2d::SEL_CallFuncND aSelector,
                                        void *pObject,
                                        float afterDelay,
                                        int tag)
{
    cocos2d::CCFiniteTimeAction *performSeq = cocos2d::CCSequence::create(cocos2d::CCDelayTime::create(afterDelay),
                                                                          cocos2d::CCCallFuncND::create(pTarget, aSelector, pObject), NULL);
    performSeq->setTag(tag);
    
    ((cocos2d::CCNode *)pTarget)->runAction(performSeq);
}

void CJUtils::performSelectorCancel(cocos2d::CCObject *pTarget,
                                              int tag)
{
    ((cocos2d::CCNode *)pTarget)->stopActionByTag(tag);
}


#pragma mark - action

void CJUtils::fadeOutAllchildren(CCNode* pNode, float duration)
{
    for (int i=0; i < ((CCArray*)pNode->getChildren())->count(); i++)
    {
        CCNode* child =  (CCNode*)((CCArray*)pNode->getChildren())->objectAtIndex(i);
        
        if (child->getChildrenCount() != 0)
        {
            fadeOutAllchildren(child, duration);
        }
        else
        {
            CCActionInterval* fadeOut_child = CCFadeOut::create(duration);
            child->runAction(fadeOut_child);
        }
    }
    
    CCActionInterval* fadeOut = CCFadeOut::create(duration);
    pNode->runAction(fadeOut);
}

void CJUtils::fadeInAllchildren(CCNode* pNode, float duration)
{
    for (int i=0; i < ((CCArray*)pNode->getChildren())->count(); i++)
    {
        CCNode* child =  (CCNode*)((CCArray*)pNode->getChildren())->objectAtIndex(i);
        
        if (child->getChildrenCount() != 0)
        {
            fadeInAllchildren(child, duration);
        }
        else
        {
            CCActionInterval* fadeIn_child = CCFadeIn::create(duration);
            child->runAction(fadeIn_child);
        }
    }
    
    CCActionInterval* fadeIn = CCFadeIn::create(duration);
    pNode->runAction(fadeIn);
}



CCActionInterval* CJUtils::getSeqAction(int nRepeatCount,
                                        float fSeqTime,
                                        std::string strSeqImageName, ...)
{
    CCAnimation *animation = CCAnimation::create();
    
    va_list args;
    va_start(args, strSeqImageName);
    
    const char *pszSeqImageName = strSeqImageName.c_str();
    while(pszSeqImageName != NULL)
    {
        animation->addSpriteFrameWithFileName(pszSeqImageName);
        animation->setDelayPerUnit(fSeqTime);
        animation->setRestoreOriginalFrame(false);
        
        pszSeqImageName = va_arg(args, const char *);
        if(pszSeqImageName == NULL)
        {
            break ;
        }
    }
    va_end(args);
    
    
    CCAnimate *seqAction = CCAnimate::create(animation);
    
    if(nRepeatCount == -1)
    {
        return CCRepeatForever::create(seqAction);
    }
    else
    {
        return CCRepeat::create(seqAction, nRepeatCount);
    }
}

CCActionInterval* CJUtils::getSeqAction(int nRepeatCount,
                                        float fSeqTime,
                                        CCObject *pCallbackTarget,
                                        SEL_CallFunc aCallbackSelector,
                                        std::string strSeqImageName, ...)
{
    CCAnimation *animation = CCAnimation::create();
    
    va_list args;
    va_start(args, strSeqImageName);
    
    const char *pszSeqImageName = strSeqImageName.c_str();
    while(pszSeqImageName != NULL)
    {
        animation->addSpriteFrameWithFileName(pszSeqImageName);
        animation->setDelayPerUnit(fSeqTime);
        animation->setRestoreOriginalFrame(false);
        
        pszSeqImageName = va_arg(args, const char *);
        if(pszSeqImageName == NULL)
        {
            break ;
        }
    }
    va_end(args);
    
    
    CCAnimate *seqAction = CCAnimate::create(animation);
    
    if(nRepeatCount == -1)
    {
        return CCRepeatForever::create(seqAction);
    }
    else
    {
        CCFiniteTimeAction *repeatAction = CCRepeat::create(seqAction, nRepeatCount);
        CCFiniteTimeAction *callbackAction = CCCallFunc::create(pCallbackTarget, aCallbackSelector);
        
        return (CCActionInterval *)CCSequence::create(repeatAction, callbackAction, NULL);
    }
}





CCAnimate* CJUtils::getAnimation(float fFrameDelay, std::string strSeqImageName, ...)
{
    CCAnimation *animation = CCAnimation::create();
    
    va_list args;
    va_start(args, strSeqImageName);
    
    const char *pszSeqImageName = strSeqImageName.c_str();
    while(pszSeqImageName != NULL)
    {
        animation->addSpriteFrameWithFileName(pszSeqImageName);
        animation->setDelayPerUnit(fFrameDelay);
        animation->setRestoreOriginalFrame(false);
        
        pszSeqImageName = va_arg(args, const char *);
        if(pszSeqImageName == NULL)
        {
            break ;
        }
    }
    va_end(args);
    
    return CCAnimate::create(animation);
}

CCActionInterval* CJUtils::getAnimations(int nRepeatCount,
                                         float fSeqTime,
                                         CCAnimate *pAnimation, ...)
{
    CCArray *actions = CCArray::create();
    
    va_list args;
    va_start(args, pAnimation);
    while (pAnimation != NULL)
    {
        actions->addObject(pAnimation);
        actions->addObject(CCDelayTime::create(fSeqTime));
        
        pAnimation = va_arg(args, CCAnimate *);
        if(pAnimation == NULL)
        {
            break ;
        }
    }
    va_end(args);
    
    
    if(nRepeatCount == -1)
    {
        return CCRepeatForever::create((CCActionInterval *)CCSequence::create(actions));
    }
    else
    {
        return CCRepeat::create(CCSequence::create(actions), nRepeatCount);
    }
}

CCActionInterval* CJUtils::getAnimations(int nRepeatCount,
                                         float fSeqTime,
                                         CCObject *pCallbackTarget,
                                         SEL_CallFunc aCallbackSelector,
                                         CCAnimate *pAnimation, ...)
{
    CCArray *actions = CCArray::create();
    
    va_list args;
    va_start(args, pAnimation);
    while (pAnimation != NULL)
    {
        actions->addObject(pAnimation);
        actions->addObject(CCDelayTime::create(fSeqTime));
        
        pAnimation = va_arg(args, CCAnimate *);
        if(pAnimation == NULL)
        {
            break ;
        }
    }
    va_end(args);
    
    if(nRepeatCount == -1)
    {
        return CCRepeatForever::create((CCActionInterval *)CCSequence::create(actions));
    }
    else
    {
        CCFiniteTimeAction *callback = CCCallFunc::create(pCallbackTarget, aCallbackSelector);
        actions->addObject(callback);
        
        return CCRepeat::create(CCSequence::create(actions), nRepeatCount);
    }
}



#pragma mark - macro define

void CJDialog(const char* pszMessage)
{
    CCMessageBox("not file Exsit ", pszMessage);
}

void CJLog(const char * pszFormat, ...)
{
    // CJLog debug
#if defined(CJ_DEBUGMODE) && CJ_DEBUGMODE == true

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    char buf[MAX_LEN];
//    
//    va_list args;
//    va_start(args, pszFormat);
//    vsnprintf(buf, MAX_LEN, pszFormat, args);
//    va_end(args);
//    
//    __android_log_print(ANDROID_LOG_DEBUG, "CJLOG : ",  buf);
#endif
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    printf("CJLOG : ");
    char szBuf[kMaxLogLen];
    
    va_list ap;
    va_start(ap, pszFormat);
    vsnprintf(szBuf, kMaxLogLen, pszFormat, ap);
    va_end(ap);
    printf("%s", szBuf);
    printf("\n");
#endif

#endif
}
