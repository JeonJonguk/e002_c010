//
//  SSQuestionItem.cpp
//  E002_C010_Project
//
//  Created by smallsnail on 2014. 4. 1..
//
//

#include "SSQuestionItem.h"
#include "CJPsdParser.h"
#include "CJUtils.h"
#include "CJMultimedia.h"

SSQuestionItem* SSQuestionItem::create(std::string pImg,
                                       std::string pTxt,
                                       std::string pSucTxt,
                                       std::string pFailTxt,
                                       std::string pSnd,
                                       std::string pSuccessSnd,
                                       std::string pFailSnd)
{
    
    SSQuestionItem* pItem = new SSQuestionItem();
    
    if(NULL!=pItem && true==pItem->init(pImg,
                                        pTxt,
                                        pSucTxt,
                                        pFailTxt,
                                        pSnd,
                                        pSuccessSnd,
                                        pFailSnd))
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


SSQuestionItem* SSQuestionItem::createWithMakeSprite(std::string pImg,
                                                     std::string pTxt,
                                                     std::string pSucTxt,
                                                     std::string pFailTxt,
                                                     std::string pSnd,
                                                     std::string pSuccessSnd,
                                                     std::string pFailSnd,
                                                     CCDictionary* pParsedDic)
{
    SSQuestionItem* pItem = new SSQuestionItem();
    
    if(NULL!=pItem && true==pItem->initWithPrams(pImg,
                                                 pTxt,
                                                 pSucTxt,
                                                 pFailTxt,
                                                 pSnd,
                                                 pSuccessSnd,
                                                 pFailSnd,
                                                 pParsedDic))
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


SSQuestionItem::SSQuestionItem()
{
    txt = "";
    sucTxt = "";
    failTxt = "";
    failSnd = "";
    successSnd = "";
    psdDic = NULL;
    string img = "";
    string snd = "";
    txtSprite = NULL;
    imgSprite = NULL;
}

SSQuestionItem::~SSQuestionItem()
{
    
}


bool SSQuestionItem::init(std::string pImg,
                          std::string pTxt,
                          std::string pSucTxt,
                          std::string pFailTxt,
                          std::string pSnd,
                          std::string pSuccessSnd,
                          std::string pFailSnd)
{
    
    img = pImg;
    txt = pTxt;
    sucTxt = pSucTxt;
    failTxt = pFailTxt;
    snd = pSnd;
    successSnd = pSuccessSnd;
    failSnd = pFailSnd;
    
    return true;
}



bool SSQuestionItem::initWithPrams(std::string pImg,
                                   std::string pTxt,
                                   std::string pSucTxt,
                                   std::string pFailTxt,
                                   std::string pSnd,
                                   std::string pSuccessSnd,
                                   std::string pFailSnd,
                                   CCDictionary* pParsedDic)
{
    
    if (this->init(pImg, pTxt, pSucTxt, pFailTxt, pSnd, pSuccessSnd, pFailSnd)) {
        

        if (psdDic) {
            
            PsdData *data = CJPsdParser::getPsdData((CCDictionary *)psdDic->objectForKey(txt));
            std::string pngName = data->file;
            pngName.append(".png");
            
            if(initWithFile(CJUtils::getInstance()->getFilePath("img",pngName).c_str()))
            {
                setPosition(data->pos);
                return true;
            }
            
        }else{
            
            if(initWithFile(CJUtils::getInstance()->getFilePath("img",txt).c_str()))
            {
                
                return true;
            }
        }
    }
    
    return false;
}



CJSprite* SSQuestionItem::createTxtSprite(CCDictionary* psdDic)
{
//    if (!txtSprite) {
        CJSprite* sp = NULL;
        if (psdDic) {
            sp = CJPsdParser::getPsdSprite(txt, psdDic);
        }else{
            sp = CJSprite::createWithFullPath(txt.c_str());
        }
        txtSprite = sp;
//    }
    return txtSprite;

}

CJSprite* SSQuestionItem::createImgSprite(CCDictionary* psdDic)
{
    CJSprite* sp = NULL;
    if (psdDic) {
        sp = CJPsdParser::getPsdSprite(img, psdDic);
    }else{
        sp = CJSprite::createWithFullPath(img.c_str());
    }
    imgSprite = sp;
    return sp;
}

void SSQuestionItem::playAction(CJSprite* sp)
{
//    imgSprite->runAction(CCSequence::create(CCScaleTo::create(0.1, 1.1, 1.2),    // |
//                                       CCScaleTo::create(0.1, 1.18, 1.05),  // -
//                                       CCScaleTo::create(0.1, 1.05, 1.1),   // |
//                                       CCScaleTo::create(0.1, 1.1, 1.03),    // -
//                                       CCScaleTo::create(0.1, 1.0, 1.0),
//                                       NULL));
    if (sp) {
        sp->stopAllActions();
        sp->runAction(CCSequence::create(CCEaseSineOut::create(CCScaleTo::create(0.15, 1.2)),
                                         CCDelayTime::create(0.2),
                                         CCEaseSineOut::create(CCScaleTo::create(0.15, 1.0)),
                                         NULL));
    }

}



#pragma mark - sound
void SSQuestionItem::playSuccessSound()
{
    CJLog("successSnd = %s", successSnd.c_str());
    CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getFilePath("snd",successSnd));
}

void SSQuestionItem::playFailSound()
{
    CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getFilePath("snd",failSnd));
}

CCCallFunc* SSQuestionItem::playFailSoundCallfunc()
{
    return CCCallFunc::create(this, callfunc_selector(SSQuestionItem::playFailSound));
}
