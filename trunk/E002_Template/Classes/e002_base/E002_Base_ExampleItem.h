//
//  E002_Base_ExampleItem.h
//  E002_Template
//
//  Created by Jeong.YJ on 2014. 2. 27..
//
//

#ifndef E002_Template_E002_Base_ExampleItem_h
#define E002_Template_E002_Base_ExampleItem_h

#include "CJLayer.h"

class E002_Base_ExampleItem
{
    
public:
    
    CC_SYNTHESIZE(int, index, Index);
    CC_SYNTHESIZE(std::string, imgPath, ImgPath);
    CC_SYNTHESIZE(std::string, selectImgPath, SelectImgPath);
    CC_SYNTHESIZE(std::string, sountPath, SoundPath);
    CC_SYNTHESIZE(int, itemTag, ItemTag);
    CC_SYNTHESIZE(int, correctTag, CorrectTag);
    CC_SYNTHESIZE(CCPoint, originalPosition, OriginalPosition);
    CC_SYNTHESIZE(CJSprite*, itemSprite, ItemSprite);
    
    
    E002_Base_ExampleItem(){};
    
    E002_Base_ExampleItem(int idx, std::string img, std::string sImg, std::string snd, int tag, int cTag)
    {
        index = idx;
        imgPath = img;
        selectImgPath = sImg;
        sountPath = snd;
        itemTag = tag;
        correctTag = cTag;
    }
    
    E002_Base_ExampleItem(int idx, std::string img, std::string snd, int tag, int cTag, CCPoint position)
    {
        index = idx;
        imgPath = img;
        sountPath = snd;
        itemTag = tag;
        correctTag = cTag;
        originalPosition = position;
    }
    
    E002_Base_ExampleItem(int idx, std::string img, std::string sImg, std::string snd, int tag, int cTag, CCPoint position)
    {
        index = idx;
        imgPath = img;
        selectImgPath = sImg;
        sountPath = snd;
        itemTag = tag;
        correctTag = cTag;
        originalPosition = position;
    }
    
};

#endif
