//
//  SSExampleItem.cpp
//  E002_C010_Project
//
//  Created by smallsnail on 2014. 3. 31..
//
//

#include "SSExampleItem.h"
#include "CJPsdParser.h"
#include "CJUtils.h"
#include "CJMultimedia.h"


SSExampleItem* SSExampleItem::create(int pIndex,
                                                     std::string pImg,
                                                     std::string pSImg,
                                                     std::string pSnd,
                                                     int pItemTag,
                                                     int pCorrectTag)
{
    
    SSExampleItem* pItem = new SSExampleItem();
    
    if(NULL!=pItem && true==pItem->init(pIndex, pImg, pSImg, pSnd, pItemTag, pCorrectTag))
    {
        pItem->autorelease();
        return pItem;
    }
    else
    {
        CC_SAFE_DELETE(pItem);
        return NULL;
    }
    
    
}


SSExampleItem* SSExampleItem::createWithMakeSprite(int pIndex,
                                                            std::string pImg,
                                                            std::string pSImg,
                                                            std::string pSnd,
                                                            int pItemTag,
                                                            int pCorrectTag,
                                                            CCDictionary* pParsedDic)
{
    SSExampleItem* pItem = new SSExampleItem();
    
    if(NULL!=pItem && true==pItem->initWithPrams(pIndex, pImg, pSImg, pSnd, pItemTag, pCorrectTag, pParsedDic))
    {
        pItem->autorelease();
        return pItem;
    }
    else
    {
        CC_SAFE_DELETE(pItem);
        return NULL;
    }
    
}


SSExampleItem::SSExampleItem()
{
    index = 0;
    img = "";
    sImg = "";
    snd = "";
    itemTag = -1;
    correctTag = -1;
    psdDic = NULL;
    sprite = NULL;
}

SSExampleItem::~SSExampleItem()
{
    
}


bool SSExampleItem::init(int pIndex,
                         std::string pImg,
                         std::string pSImg,
                         std::string pSnd,
                         int pItemTag,
                         int pCorrectTag)
{
    index = pIndex;
    img = pImg;
    sImg = pSImg;
    snd = pSnd;
    itemTag = pItemTag;
    correctTag = pCorrectTag;

    return true;
}

bool SSExampleItem::initWithPrams(int pIndex,
                                          std::string pImg, std::string pSImg, std::string pSnd,
                                          int pItemTag, int pCorrectTag, CCDictionary* pParsedDic)
{
    index = pIndex;
    img = pImg;
    sImg = pSImg;
    snd = pSnd;
    itemTag = pItemTag;
    correctTag = pCorrectTag;
    psdDic = pParsedDic;
    
    if (psdDic) {
        
        PsdData *data = CJPsdParser::getPsdData((CCDictionary *)psdDic->objectForKey(img));
        std::string pngName = data->file;
        pngName.append(".png");
        
        if(initWithFile(CJUtils::getInstance()->getFilePath("img",pngName).c_str()))
        {
            setPosition(data->pos);
            return true;
        }
        
    }else{
        if(initWithFile(CJUtils::getInstance()->getFilePath("img",img).c_str()))
        {
            
            return true;
        }
    }
    
    return false;
    
}

CJSprite* SSExampleItem::createImgSprite(CCDictionary* psdDic)
{
    CJSprite* sp = NULL;
//    CJLog("img = %s", img.c_str());
    if (psdDic) {
        sp = CJPsdParser::getPsdSprite(img, psdDic);
    }else{
        sp = CJSprite::createWithFullPath(img.c_str());
    }
    sprite = sp;
    return sp;
}


void SSExampleItem::playAction()
{
    
    sprite->stopAllActions();
    sprite->runAction(CCSequence::create(CCEaseSineOut::create(CCScaleTo::create(0.15, 1.2)),
                                         CCDelayTime::create(0.2),
                                         CCEaseSineOut::create(CCScaleTo::create(0.15, 1.0)),
                                         NULL));
}
