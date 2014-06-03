//
//  SSExampleItem.h
//  E002_C010_Project
//
//  Created by smallsnail on 2014. 3. 31..
//
//

#ifndef E002_C010_Project_SSExampleItem_h
#define E002_C010_Project_SSExampleItem_h

#include "SSItem.h"


class SSExampleItem : public SSItem
{
public:
    int             index;
    std::string     sImg;
    int             itemTag;
    int             correctTag;
    CCDictionary*   psdDic;
    //    std::string     img;
    //    std::string     snd;
    
    CJSprite*       sprite;
    
    SSExampleItem();
    ~SSExampleItem();
    
    
    
    static SSExampleItem* create(int pIndex,
                                         std::string pImg,
                                         std::string pSImg,
                                         std::string pSnd,
                                         int pItemTag,
                                         int pCorrectTag);
    
    
    static SSExampleItem* createWithMakeSprite(int pIndex,
                                                std::string pImg,
                                                std::string pSImg,
                                                std::string pSnd,
                                                int pItemTag,
                                                int pCorrectTag,
                                                CCDictionary* pParsedDic);
    
    bool init(int pIndex,
              std::string pImg,
              std::string pSImg,
              std::string pSnd,
              int pItemTag,
              int pCorrectTag);
    
    bool initWithPrams(int pIndex,
                               std::string pImg,
                               std::string pSImg,
                               std::string pSnd,
                               int pItemTag,
                               int pCorrectTag,
                               CCDictionary* pParsedDic);
    
    
    CJSprite* createImgSprite(CCDictionary* psdDic = NULL);
    
    void playAction();
};

#endif
