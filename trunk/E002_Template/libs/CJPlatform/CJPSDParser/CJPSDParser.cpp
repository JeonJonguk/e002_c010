//
//  CJPsdParser.cpp
//  SoundPhonics_Template
//
//  Created by j2enty on 13. 6. 11..
//
//

#include "CJPsdParser.h"
#include "CJUtils.h"

using namespace cocos2d;


#define ENCODE_TYPE_UTF8                                "UTF-8"



rapidjson::Document CJPsdParser::initParse(const char *pageName)
{
    
    rapidjson::Document document;
    
    std::string filename = CCFileUtils::sharedFileUtils()->fullPathForFilename(pageName);
    CCLog(" jekim84 filename %s", filename.c_str());
    
    unsigned long buffsize = 0;
    unsigned char* pData = NULL;
    
    char* pszRet = 0;
    pData = CCFileUtils::sharedFileUtils()->getFileData(filename.c_str(), "rb", &buffsize);
    do
    {
        CC_BREAK_IF(!pData || buffsize <= 0);
        pszRet = new char[buffsize+1];
        pszRet[buffsize] = '\0';
        memcpy(pszRet, pData, buffsize);
        CC_SAFE_DELETE_ARRAY(pData);
    } while (false);
    
    
    if (document.Parse<0>(pszRet).HasParseError())
    {
        CCLog("document ParseError");
    }
    else
    {
        CCLog("document ParseSuccess");
    }
    
    // add Memory leak by Lee.YJ at 2013.03.07
    CC_SAFE_DELETE(pszRet);
    
    
    return document;
}


void CJPsdParser::parseToPsdJSON(std::string strPsdFileName,
                                cocos2d::CCDictionary **pPsdDict,
                                bool bIsCommonPath /* = false */)
{
    CJPsdParser *psdParser = new CJPsdParser();
    psdParser->_setPsdData(pPsdDict);
    
    std::string rootPath;
    if (!bIsCommonPath) {
        rootPath = CJUtils::getInstance()->getResourcePath();
    }
    else
    {
        rootPath = CJUtils::getInstance()->getCommonResourcePath();
    }
    std::string tempFileName = rootPath.append("json/");
    tempFileName.append(strPsdFileName);

    psdParser->setElement(CJPsdParser::initParse(tempFileName.c_str()));
    
    delete psdParser;
}

void CJPsdParser::parseToPsdXML(std::string strPsdFileName,
                                cocos2d::CCDictionary **pPsdDict,
                                bool bIsCommonPath /* = false */)
{
    CJPsdParser *psdParser = new CJPsdParser();
    psdParser->_setPsdData(pPsdDict);
    
    std::string rootPath;
    if (!bIsCommonPath) {
        rootPath = CJUtils::getInstance()->getResourcePath();
    }
    else
    {
        rootPath = CJUtils::getInstance()->getCommonResourcePath();
    }
    std::string tempFileName = rootPath.append("xml/");
    tempFileName.append(strPsdFileName);

    
    CCSAXParser xmlParser;
    xmlParser.init(ENCODE_TYPE_UTF8);
    xmlParser.setDelegator(psdParser);
    xmlParser.parse(tempFileName.c_str());
    
    delete psdParser;
}

CJPsdParser::CJPsdParser()
{
    _psdDatas       = NULL;
    _data           = new PsdData();
}

CJPsdParser::~CJPsdParser()
{
    _psdDatas       = NULL;
    delete          _data;
}


void CJPsdParser::setElement(rapidjson::Document document)
{
    if (document.HasMember("layer"))
    {
        const rapidjson::Value& layer = document["layer"];
            
        for (int layerIdx = 0; layerIdx < layer.Size(); layerIdx++)
        {
            const rapidjson::Value& layerObj = layer[layerIdx];
            
            CCDictionary *tempDict = CCDictionary::create();
        
            if (layerObj.HasMember("name"))
            {
                _data->key = layerObj["name"].GetString();
                _data->name = layerObj["name"].GetString();

                tempDict->setObject(CCString::create(_data->name), "name");
                
                std::string tempStr         = CCString::create(_data->name)->getCString();
                std::string delimiterDot    = ".";
                std::string delimiterAt     = "@";
                tempStr = tempStr.substr(0, tempStr.find(delimiterDot));
                tempStr = tempStr.substr(0, tempStr.find(delimiterAt));
                
                tempDict->setObject(CCString::create(tempStr), "file");
            }
            
            if(layerObj.HasMember("width"))
            {
                _data->size.width = layerObj["width"].GetDouble();
                tempDict->setObject(CCFloat::create(_data->size.width), "width");

            }
            
            if(layerObj.HasMember("height"))
            {
                _data->size.height = layerObj["height"].GetDouble();
                tempDict->setObject(CCFloat::create(_data->size.height), "height");
            }
            
            if(layerObj.HasMember("posX"))
            {
                _data->pos.x = layerObj["posX"].GetDouble();
                tempDict->setObject(CCFloat::create(_data->pos.x), "posX");
            }
            
            if(layerObj.HasMember("posY"))
            {
                _data->pos.y = layerObj["posY"].GetDouble();
                tempDict->setObject(CCFloat::create(_data->pos.y), "posY");
            }
            
            _psdDatas->setObject(tempDict, _data->key);
            
            this->_resetPsdData();
        }
    }
}

void CJPsdParser::startElement(void *ctx, const char *name, const char **atts)
{
    CC_UNUSED_PARAM(ctx);
    
    if(true == _isStringCompare(name, "layer"))
    {
        while(NULL != *atts)
        {
            if(true == _isStringCompare(*atts, "name"))
            {
                _data->key = * ++atts;
                _data->name = * atts;
            }
            else if(true == _isStringCompare(*atts, "openGLpositionCenterX"))
            {
                _data->pos.x = CCString::create(* ++atts)->floatValue();
            }
            else if(true == _isStringCompare(*atts, "openGLpositionCenterY"))
            {
                _data->pos.y = CCString::create(* ++atts)->floatValue();
            }
            else if(true == _isStringCompare(*atts, "layerwidth"))
            {
                _data->size.width = CCString::create(* ++atts)->floatValue();
            }
            else if(true == _isStringCompare(*atts, "layerheight"))
            {
                _data->size.height = CCString::create(* ++atts)->floatValue();
            }
            
            atts++;
        }
    }
}

void CJPsdParser::endElement(void *ctx, const char *name)
{
    
}

void CJPsdParser::textHandler(void *ctx, const char *s, int len)
{
    CCDictionary *tempDict = CCDictionary::create();
    
    std::string tempStr         = s;
    std::string delimiterDot    = ".";
    std::string delimiterAt     = "@";
    tempStr = tempStr.substr(0, tempStr.find(delimiterDot));
    tempStr = tempStr.substr(0, tempStr.find(delimiterAt));
    tempDict->setObject(CCString::create(tempStr), "file");
    
    tempDict->setObject(CCString::create(_data->name), "name");
    tempDict->setObject(CCFloat::create(_data->pos.x), "posX");
    tempDict->setObject(CCFloat::create(_data->pos.y), "posY");
    tempDict->setObject(CCFloat::create(_data->size.width), "width");
    tempDict->setObject(CCFloat::create(_data->size.height), "height");
    _psdDatas->setObject(tempDict, _data->key);

    this->_resetPsdData();
}

void CJPsdParser::_setPsdData(cocos2d::CCDictionary **pPsdDict)
{
    _psdDatas = NULL;
    _psdDatas = *pPsdDict;
}




void CJPsdParser::_resetPsdData()
{
    _data->key      = "";
    _data->name     = "";
    _data->pos      = CCPointZero;
    _data->size     = CCSizeZero;
}

bool CJPsdParser::_isStringCompare(std::string firstStr, std::string secondStr)
{
    return firstStr.compare(secondStr) == 0 ? true : false;
}


PsdData* CJPsdParser::getPsdData(cocos2d::CCDictionary *pPsdDatas)
{
    PsdData *tempData = new PsdData();    
    tempData->name          = ((CCString *)pPsdDatas->objectForKey("name"))->getCString();
    tempData->file          = ((CCString *)pPsdDatas->objectForKey("file"))->getCString();
    tempData->pos.x         = ((CCFloat *)pPsdDatas->objectForKey("posX"))->getValue();
    tempData->pos.y         = ((CCFloat *)pPsdDatas->objectForKey("posY"))->getValue();
    tempData->size.width    = ((CCFloat *)pPsdDatas->objectForKey("width"))->getValue();
    tempData->size.height   = ((CCFloat *)pPsdDatas->objectForKey("height"))->getValue();
    
    return tempData;
}

CJSprite* CJPsdParser::getPsdSprite(std::string strResName, cocos2d::CCDictionary *pPsdDatas)
{

    PsdData *data = CJPsdParser::getPsdData((CCDictionary *)pPsdDatas->objectForKey(strResName));
    
//    std::string tempFileName = "img/";
//    tempFileName.append(data->name);
    
    std::string pngName = data->file;
    std::string jpgName = data->file;
    pngName.append(".png");
    jpgName.append(".jpg");
    
    
    CJSprite *tempSprite = CJSprite::createWithFullPath(pngName.c_str());
    
    if(NULL == tempSprite)
    {
        tempSprite = CJSprite::createWithFullPath(jpgName.c_str());
    }
    if(NULL == tempSprite)
    {
        CCLog("NO IMAGE FILE!");
    }
    
    tempSprite->setPosition(data->pos);

    delete data;
    
    return tempSprite;
}

CJSprite* CJPsdParser::getPsdCommonSprite(std::string strResName, cocos2d::CCDictionary *pPsdDatas)
{
    
    PsdData *data = CJPsdParser::getPsdData((CCDictionary *)pPsdDatas->objectForKey(strResName));

    
    std::string pngName = data->file;
    std::string jpgName = data->file;
    pngName.append(".png");
    jpgName.append(".jpg");
    
    
    CJSprite *tempSprite = CJSprite::createWithCommonPath(pngName.c_str());
    
    if(NULL == tempSprite)
    {
        tempSprite = CJSprite::createWithCommonPath(jpgName.c_str());
    }
    if(NULL == tempSprite)
    {
        CCLog("NO IMAGE FILE!");
    }
    
    tempSprite->setPosition(data->pos);
    
    delete data;
    
    return tempSprite;
}

CCPoint CJPsdParser::getPsdPosition(std::string strResName, cocos2d::CCDictionary *pPsdDatas)
{
    PsdData *data = CJPsdParser::getPsdData((CCDictionary *)pPsdDatas->objectForKey(strResName));
    CCPoint pos = data->pos;
    delete data;
    
    return pos;
}

CCSize CJPsdParser::getPsdSize(std::string strResName, cocos2d::CCDictionary *pPsdData)
{
    PsdData *data = CJPsdParser::getPsdData((CCDictionary *)pPsdData->objectForKey(strResName));
    CCSize size = data->size;
    delete data;
    
    return size;
}
