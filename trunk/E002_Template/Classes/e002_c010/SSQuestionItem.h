//
//  SSQuestionItem.h
//  E002_C010_Project
//
//  Created by smallsnail on 2014. 4. 1..
//
//

#ifndef E002_C010_Project_SSQuestionItem_h
#define E002_C010_Project_SSQuestionItem_h

#include "SSItem.h"


class SSQuestionItem : public SSItem
{
public:
    
    std::string txt;
    std::string sucTxt;
    std::string failTxt;
    std::string failSnd;
    std::string successSnd;
    CCDictionary*   psdDic;
    //    std::string img = "";
    //    std::string snd = "";
    
    CJSprite*       txtSprite;
    CJSprite*       imgSprite;


    
    SSQuestionItem();
    ~SSQuestionItem();
    
    
    
    static SSQuestionItem* create(std::string pImg,
                                  std::string pTxt,
                                  std::string pSucTxt,
                                  std::string pFailTxt,
                                  std::string pSnd,
                                  std::string pSuccessSnd,
                                  std::string pFailSnd);
    
    static SSQuestionItem* createWithMakeSprite(std::string pImg,
                                                std::string pTxt,
                                                std::string pSucTxt,
                                                std::string pFailTxt,
                                                std::string pSnd,
                                                std::string pSuccessSnd,
                                                std::string pFailSnd,
                                                CCDictionary* pParsedDic);
    
    
    bool init(std::string pImg,
              std::string pTxt,
              std::string pSucTxt,
              std::string pFailTxt,
              std::string pSnd,
              std::string pSuccessSnd,
              std::string pFailSnd);
    
    bool initWithPrams(std::string pImg,
                       std::string pTxt,
                       std::string pSucTxt,
                       std::string pFailTxt,
                       std::string pSnd,
                       std::string pSuccessSnd,
                       std::string pFailSnd,
                       CCDictionary* pParsedDic);
    

    //sprite
    CJSprite* createTxtSprite(CCDictionary* psdDic = NULL);
    CJSprite* createImgSprite(CCDictionary* psdDic = NULL);
    
    //action
    void playAction(CJSprite* sp);
    
    //sound
    void playSuccessSound();
    void playFailSound();
    CCCallFunc* playFailSoundCallfunc();
};


#endif
