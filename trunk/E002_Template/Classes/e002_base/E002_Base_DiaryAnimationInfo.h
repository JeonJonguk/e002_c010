//
//  E002_Base_DiaryAnimationInfo.h
//  E002_Template
//
//  Created by Jeong.YJ on 2014. 4. 29..
//
//

#ifndef E002_Template_E002_Base_DiaryAnimationInfo_h
#define E002_Template_E002_Base_DiaryAnimationInfo_h

class E002_Base_DiaryAnimationInfo
{
public:
    CC_SYNTHESIZE(int, tag, Tag);
    CC_SYNTHESIZE(std::string, aniName, AniName);
    CC_SYNTHESIZE(int, number, Number);
    CC_SYNTHESIZE(float, posX, PositionX);
    CC_SYNTHESIZE(float, posY, PositionY);
};

#endif
