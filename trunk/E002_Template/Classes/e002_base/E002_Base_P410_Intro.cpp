//
//  E002_C030_ImageGuide.cpp
//  SoundPhonics_Template
//
//  Created by whitems on 13. 7. 5..
//
//

#include "E002_Base_P410_Intro.h"
#include "CJUtils.h"

namespace  {
enum
{
    kTagBlank = 100,
    kTagWord,
    
    kTagSentence = 200,

};
}

E002_Base_P410_Intro::~E002_Base_P410_Intro()
{
    delete m_psdDictionary;
}

E002_Base_P410_Intro::E002_Base_P410_Intro()
{
    m_psdDictionary = new CCDictionary();
    mCompleteWrite = false;
    mSentencesDelays = new std::vector<float>();
}



#pragma mark - init
bool E002_Base_P410_Intro::init()
{
    if (!CJLayer::initWithColor(ccc4(255, 255, 255, 255))) {
        return false;
    }
    
    mCurrentDiary = CJUtils::getInstance()->getUserDefaultIntegerForKey(E002_USERDEFAULT_DIARY_NUMBER);

    return true;
}

int E002_Base_P410_Intro::getCurrentDiaryNumber()
{
    return mCurrentDiary;
}

void E002_Base_P410_Intro::onEnter()
{
    CJLayer::onEnter();
    addWriteCompleteObserver();
    addSoundObserver();
}

void E002_Base_P410_Intro::onExit()
{
    CJLayer::onExit();
    removeWriteCompleteObserver();
    removeSoundObserver();
}

void E002_Base_P410_Intro::onViewLoad()
{
	CJLayer::onViewLoad();
    
}

void E002_Base_P410_Intro::onViewLoaded()
{
	CJLayer::onViewLoaded();
    
    CJSprite* drawLine = CJSprite::createWithFullPath(getContentID(CJUtils::getStringFormatInteger("_p410_intro_img_line%02d.png", mCurrentDiary - DIARY_1)).c_str());
	drawLine->setPosition(winCenter);
	addChild(drawLine, kDepth0_backImage);
    
    for (int i = 0; i < mSentencesDelays->size() - 1; i++)
    {
        std::string tempNum = CJUtils::getStringFormatInteger("_%02d", i);
        std::string fileName = getContentID(CJUtils::getStringFormatInteger("_p410_intro_img_%02d_sentence", mCurrentDiary - DIARY_1));
        
        fileName.append(tempNum);
        std::string positionName = fileName;

        CJSprite *sentence = CJSprite::createWithFullPath(fileName.append(".png").c_str());
        sentence->setPosition(CJPsdParser::getPsdPosition(positionName, m_psdDictionary));
        addChild(sentence, kDepth0_backImage+1, kTagSentence + i);
    }
    
    CJSprite *blank = CJSprite::createWithFullPath(getContentID(CJUtils::getStringFormatInteger("_p410_intro_img_%02d_blank.png", mCurrentDiary - DIARY_1)).c_str());
    blank->setPosition(CJPsdParser::getPsdPosition(getContentID(CJUtils::getStringFormatInteger("_p410_intro_img_%02d_blank", mCurrentDiary - DIARY_1)), m_psdDictionary));
    addChild(blank, kDepth0_backImage+1, kTagBlank);
    
    mTargetPoint = blank->getPosition();
    
    CCRepeat *repeat = CCRepeat::create(CCSequence::create(CCScaleTo::create(0.4f, 0.85),
                                                           CCScaleTo::create(0.4f, 1.0),
                                                           NULL), -1);
    
    blank->runAction(repeat);
    
    
    createIndexBtn();
    
    playCommonEffect("e002_common_diary_sfx_box.mp3", true);
}

void E002_Base_P410_Intro::setSentencesDelays(std::vector<float> *sentencesDelays)
{
    mSentencesDelays = sentencesDelays;
}

#pragma mark - touch

bool E002_Base_P410_Intro::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint tp = pTouch->getLocation();

    if (!mCompleteWrite && getChildByTag(kTagBlank) != NULL && CJUtils::hitTestPoint(getChildByTag(kTagBlank), tp, false))
    {
        stopAllEffect();
        onTouchedBlank();
        playCommonEffect("e002_common_sfx_box_02.mp3");
    }
    else if(getChildByTag(kTagWord) != NULL && CJUtils::hitTestPoint(getChildByTag(kTagWord), tp, false))
    {
        mTouchingWordSp = (CJSprite*)getChildByTag(kTagWord);
        mTouchingWordSp->stopAllActions();
        mTouchingWordSp->setScale(1.3f);
        
        mTouchedPointGab = ccpSub(mTouchingWordSp->getPosition(), tp);
    
        CCRepeat *repeat = CCRepeat::create(CCSequence::create(CCFadeTo::create(0.5f, 80),
                                                               CCFadeTo::create(0.5f, 255),
                                                               NULL), -1);
        
        getChildByTag(kTagBlank)->runAction(repeat);
        
        return true;
    }
    
    return false;
}

void E002_Base_P410_Intro::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint tp = pTouch->getLocation();
    mTouchingWordSp->setPosition(ccp(tp.x + mTouchedPointGab.x, tp.y + mTouchedPointGab.y));
}

void E002_Base_P410_Intro::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    getChildByTag(kTagBlank)->stopAllActions();
    
    CJSprite *blank = (CJSprite*)getChildByTag(kTagBlank);

        
    if (CJUtils::hitTestPoint(mTouchingWordSp, blank->getPosition(), false))
    {
        intoBlank();
        return;
    }
    
    mTouchingWordSp->runAction(CCSpawn::create(CCEaseBackOut::create(CCMoveTo::create(0.1, mWordOriginalPosition)),
                                                   CCScaleTo::create(0.1, 1.0),
                                                   NULL));
}

void E002_Base_P410_Intro::intoBlank()
{
    getChildByTag(kTagBlank)->setVisible(false);
    
    mTouchingWordSp->runAction(CCSequence::create(CCSpawn::create(CCMoveTo::create(0.1, getChildByTag(kTagBlank)->getPosition()),
                                                                   CCScaleTo::create(0.1, 1.0),
                                                                  NULL),
                                                  CCDelayTime::create(0.2),
                                                  CCCallFunc::create(this, callfunc_selector(E002_Base_P410_Intro::changeWord)),
                                                  CCCallFunc::create(this, callfunc_selector(E002_Base_P410_Intro::showParticle)),
                                                  CCDelayTime::create(1.0f),
                                                  CCCallFunc::create(this, callfunc_selector(E002_Base_P410_Intro::replaceDrawScene)),
                                                  NULL));
    
    
}

void E002_Base_P410_Intro::showParticle()
{
    playNarration(getContentID(CJUtils::getStringFormatInteger("_p410_snd_word_%02d_as.mp3", mCurrentDiary - DIARY_1 + 1)));
    
    removeChildByTag(kTagBlank);
    
    CCParticleSystemQuad * particle = CCParticleSystemQuad::create(getCommonFilePath("img","e002_common_diary_star.plist").c_str());
    addChild(particle, kDepth7_popup+1);
    particle->setPosition(getChildByTag(kTagWord)->getPosition());
    particle->setAutoRemoveOnFinish(true);
}

void E002_Base_P410_Intro::changeWord()
{
    std::string changeWord = getContentID(CJUtils::getStringFormatInteger("_p410_intro_img_%02d_word_01.png", mCurrentDiary - DIARY_1));

    mTouchingWordSp->setTexture(CCTextureCache::sharedTextureCache()->
                       addImage(CJUtils::getInstance()->getFilePath("img", changeWord).c_str()));

}

void E002_Base_P410_Intro::createIndexBtn()
{
    CJSprite *indexN = CJSprite::createWithCommonPath("e002_common_diary_btn_index_n.png");
    CJSprite *indexS = CJSprite::createWithCommonPath("e002_common_diary_btn_index_s.png");
    
    CCMenuItemSprite* indexBtn = CCMenuItemSprite::create(indexN,
                                                          indexS,
                                                          this,
                                                          menu_selector(E002_Base_P410_Intro::selectIndexBtn));
    
    indexBtn->setPosition(ccp(49, 695.2));
    
    
    CCMenu *btns = CCMenu::create(indexBtn, NULL);
    btns->setPosition(CCPointZero);
    
    
    addChild(btns);

}

void E002_Base_P410_Intro::completeWriteCallback()
{
    mCompleteWrite = true;
    
    getChildByTag(kTagBlank)->stopAllActions();
    ((CJSprite*)getChildByTag(kTagBlank))->setVisible(false);
    //removeChildByTag(kTagBlank);
    
    CJSprite *word = CJSprite::createWithFullPath(getContentID(CJUtils::getStringFormatInteger("_p410_intro_img_%02d_word_01.png", mCurrentDiary - DIARY_1)).c_str());
    word->setPosition(getChildByTag(kTagBlank)->getPosition());
    addChild(word, kDepth0_backImage+1, kTagWord);

    word->setScale(0);
    mWordOriginalPosition = word->getPosition();

    playCommonEffect("e002_common_diary_sfx_word_ok.mp3");
    
    word->runAction(CCSequence::create(CCDelayTime::create(0.3f),
                                       CCCallFunc::create(this, callfunc_selector(E002_Base_P410_Intro::showParticle)),
                                       CCEaseElasticOut::create(CCScaleTo::create(1, 1.0)),
                                       //CCDelayTime::create(1.0f),
                                       //CCCallFunc::create(this, callfunc_selector(E002_Base_P410_Intro::replaceDrawScene)),
                                       NULL));
}

void E002_Base_P410_Intro::closeWriteCallback()
{
    playCommonEffect("e002_common_diary_sfx_box.mp3", true);
}

void E002_Base_P410_Intro::onTouchedBlank()
{
    playBtnEffect();
}

void E002_Base_P410_Intro::onNarrationFinishedCallback(std::string fileName)
{
    if (mCompleteWrite)
    {
        if (fileName == getContentID(CJUtils::getStringFormatInteger("_p410_snd_word_%02d_as.mp3", mCurrentDiary - DIARY_1 + 1)))
        {
            playNarration(getContentID(CJUtils::getStringFormatInteger("_p410_snd_script_%02d_as.mp3", mCurrentDiary - DIARY_1 + 1)));
            
            for (int i = 0; i < mSentencesDelays->size(); i++)
            {
                if (getChildByTag(kTagSentence + i) != NULL)
                {
                    getChildByTag(kTagSentence + i)->runAction(CCSequence::create(CCDelayTime::create(mSentencesDelays->at(i)),
                                                                                  CCScaleTo::create(0.2f, 1.2),
                                                                                  CCScaleTo::create(0.2f, 1.0f),
                                                                                  NULL));
                    
                }
                
                if (i == mSentencesDelays->size() - 1)
                {
                    getChildByTag(kTagWord)->runAction(CCSequence::create(CCDelayTime::create(mSentencesDelays->at(i)),
                                                                          CCScaleTo::create(0.2f, 1.2),
                                                                          CCScaleTo::create(0.2f, 1.0f),
                                                                          NULL));
                }
            }
        }
        else if(fileName == getContentID(CJUtils::getStringFormatInteger("_p410_snd_script_%02d_as.mp3", mCurrentDiary - DIARY_1 + 1)))
        {
            replaceDrawScene();
        }
    }
}

std::string E002_Base_P410_Intro::getContentID(std::string resource)
{
    return CJUtils::getInstance()->getContentID().append(resource);
}

void E002_Base_P410_Intro::playBtnEffect()
{
    CJMultimedia::getInstance()->playEffect(CJUtils::getInstance()->getCommonFilePath("snd","e002_common_sfx_btn_01.mp3"));
}

void E002_Base_P410_Intro::addWriteCompleteObserver()
{
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(E002_Base_P410_Intro::completeWriteCallback),
                                                                  E002_NOTIFICATION_DIARY_WRITE_FINISHCALL,
                                                                  NULL);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(E002_Base_P410_Intro::closeWriteCallback),
                                                                  E002_NOTIFICATION_DIARY_WRITE_CLOSECALL,
                                                                  NULL);

}

void E002_Base_P410_Intro::removeWriteCompleteObserver()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, E002_NOTIFICATION_DIARY_WRITE_FINISHCALL);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, E002_NOTIFICATION_DIARY_WRITE_CLOSECALL);
}