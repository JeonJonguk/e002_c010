//
//  E001_C010_Common_ResourceManager.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 7. 14..
//
//

#ifndef E002_C010_BaseUtil_h
#define E002_C010_BaseUtil_h

#include "CJAnimationManager.h"

#define FLASH_ANISON            "ANISON"
#define FLASH_GRUM              "GRUMBIE"
#define FLASH_BOOM              "BOOM"
#define FLASH_CHU               "CHU"
#define FLASH_ROBOT             "ROBOT"
#define FLASH_OTHERONE          "OTHER_ONE"

#define FLASH_KEY_LOOPING       "looping"
#define FLASH_KEY_LOOPING2      "looping2"
#define FLASH_KEY_SUCCESS       "success"
#define FLASH_KEY_FAIL          "fail"
#define FLASH_KEY_SPEAK         "speak"
#define FLASH_KEY_ACTION1       "action1"
#define FLASH_KEY_ACTION2       "action2"
#define FLASH_KEY_RUN           "run"


static const char* wordSoundFileNames[] =
{
    "no file(index:0)",
    "e002_c010_p000_snd_01_magic e_n.mp3",
    "e002_c010_p000_snd_02_a_n.mp3",
    "e002_c010_p000_snd_03_i_n.mp3",
    "e002_c010_p000_snd_04_cape_n.mp3",
    "e002_c010_p000_snd_05_tape_n.mp3",
    "e002_c010_p000_snd_06_date_n.mp3",
    "e002_c010_p000_snd_07_gate_n.mp3",
    "e002_c010_p000_snd_08_cake_n.mp3",
    "e002_c010_p000_snd_09_bake_n.mp3",
    "e002_c010_p000_snd_10_game_n.mp3",
    
    "e002_c010_p000_snd_11_name_n.mp3",
    "e002_c010_p000_snd_12_kite_n.mp3",
    "e002_c010_p000_snd_13_bite_n.mp3",
    "e002_c010_p000_snd_14_ride_n.mp3",
    "e002_c010_p000_snd_15_hide_n.mp3",
    "e002_c010_p000_snd_16_line_n.mp3",
    "e002_c010_p000_snd_17_vine_n.mp3",
    "e002_c010_p000_snd_18_five_n.mp3",
    "e002_c010_p000_snd_19_dive_n.mp3",
    "e002_c010_p000_snd_20_cap_n.mp3",
    
    "e002_c010_p000_snd_21_tap_n.mp3",
    "e002_c010_p000_snd_22_cak_n.mp3",
    "e002_c010_p000_snd_23_bak_n.mp3",
    "e002_c010_p000_snd_24_dat_n_backup.mp3",
    "e002_c010_p000_snd_25_gat_n_backup.mp3",
    "e002_c010_p000_snd_26_gam_n_backup.mp3",
    "e002_c010_p000_snd_27_nam_n_backup.mp3",
    "e002_c010_p000_snd_28_kit_n.mp3",
    "e002_c010_p000_snd_29_bit_n.mp3",
    "e002_c010_p000_snd_30_fiv_n.mp3",
    
    "e002_c010_p000_snd_31_div_n.mp3",
    "e002_c010_p000_snd_32_rid_n_backup.mp3",
    "e002_c010_p000_snd_33_hid_n_backup.mp3",
    "e002_c010_p000_snd_34_lin_n_backup.mp3",
    "e002_c010_p000_snd_35_vin_n_backup.mp3",
    "e002_c010_p000_snd_36_nime_n.mp3",
    "e002_c010_p000_snd_37_hade_n.mp3",
    "e002_c010_p000_snd_38_bike_n.mp3",
    "e002_c010_p000_snd_39_vane_n.mp3",
    "e002_c010_p000_snd_40_cipe_n_bakeup.mp3",
    
    "e002_c010_p000_snd_41_dite_n_bakeup.mp3",
    "e002_c010_p000_snd_42_kate_n_bakeup.mp3",
    "e002_c010_p000_snd_43_fave_n_bakeup.mp3",
    "e002_c010_p000_snd_44_t_n.mp3",
    "e002_c010_p000_snd_45_n_n.mp3",
    "e002_c010_p000_snd_46_t_ape_n.mp3",
    "e002_c010_p000_snd_47_n_ape_n.mp3",
    "e002_c010_p000_snd_48_c_n.mp3",
    "e002_c010_p000_snd_49_g_n.mp3",
    "e002_c010_p000_snd_50_c_ape_n.mp3",
    
    "e002_c010_p000_snd_51_g_ape_n.mp3",
    "e002_c010_p000_snd_52_l_n.mp3",
    "e002_c010_p000_snd_53_m_n.mp3",
    "e002_c010_p000_snd_54_l_ine_n.mp3",
    "e002_c010_p000_snd_55_m_ine_n.mp3",
    "e002_c010_p000_snd_56_v_n.mp3",
    "e002_c010_p000_snd_57_p_n.mp3",
    "e002_c010_p000_snd_58_v_ine_n.mp3",
    "e002_c010_p000_snd_59_p_ine_n.mp3",
    "e002_c010_p000_snd_60_h_n.mp3",
    
    "e002_c010_p000_snd_61_h_ide_n.mp3",
    "e002_c010_p000_snd_62_t_ide_n.mp3",
    "e002_c010_p000_snd_63_r_n.mp3",
    "e002_c010_p000_snd_64_w_n.mp3",
    "e002_c010_p000_snd_65_r_ide_n.mp3",
    "e002_c010_p000_snd_66_w_ide_n.mp3",
    
    "e002_c010_p000_snd_67_ape_n.mp3",
    "e002_c010_p000_snd_68_ame_n.mp3",
    "e002_c010_p000_snd_69_ate_n.mp3",
    "e002_c010_p000_snd_70_ake_n.mp3",
    "e002_c010_p000_snd_71_ide_n.mp3",
    "e002_c010_p000_snd_72_ite_n.mp3",
    "e002_c010_p000_snd_73_ine_n.mp3",
    "e002_c010_p000_snd_74_ive_n.mp3",
};



class E002_C010_BaseUtil
{
public:
    
    static void OnLastFrame(CJAnimation* pAnimation)
    {
        if (pAnimation->getKey() == FLASH_KEY_FAIL)
        {
            CCNode* parent = pAnimation->getParent();
            int depth = pAnimation->getZOrder();
            pAnimation->stopAnimation();
            CJAnimation* loop = pAnimation->getDataPool()->getAnimationFromAnimationKey(FLASH_KEY_LOOPING);
            parent->addChild(loop, depth);
            loop->playAnimationRepeatCount(-1);
            return;
        }
        
        else if (pAnimation->getKey() == FLASH_KEY_SUCCESS)
        {
            CCNode* parent = pAnimation->getParent();
            int depth = pAnimation->getZOrder();
            pAnimation->stopAnimation();
            CJAnimation* loop = pAnimation->getDataPool()->getAnimationFromAnimationKey(FLASH_KEY_LOOPING);
            parent->addChild(loop, depth);
            loop->playAnimationRepeatCount(-1);
            return;
        }

    }

    
    static CJSprite* copyCJSprite(CJSprite* source)
    {
        CJSprite* clone = new CJSprite();
        clone->initWithTexture(source->getTexture());
        clone->autorelease();
        
        CCObject* srcSubnode = NULL;
        
        CCARRAY_FOREACH(source->getChildren(), srcSubnode)
        {
            CJSprite* subnode;
            if(dynamic_cast<CJSprite*>(srcSubnode))
            {
                CJSprite* srcSprite = (CJSprite*)srcSubnode;
                
                subnode = new CJSprite();
                subnode->initWithTexture(srcSprite->getTexture());
                subnode->autorelease();
                
//                subnode = CJSprite::createWithTexture(srcSprite->getTexture());
                ((CJSprite*)subnode)->setDisplayFrame(srcSprite->displayFrame());
            } else {
                subnode = copyCJSprite((CJSprite*)srcSubnode);
            }
            
            subnode->setRotation(((CJSprite*)srcSubnode)->getRotation());
            subnode->setPosition(((CJSprite*)srcSubnode)->getPosition());
            subnode->setAnchorPoint(((CJSprite*)srcSubnode)->getAnchorPoint());
            subnode->setZOrder(((CJSprite*)srcSubnode)->getZOrder());
            
            clone->addChild(subnode);
        }
        
        
//        if (source->getChildren() == 0)
//        {
//            CJSprite* srcSprite = (CJSprite*)source;
//            CJSprite* subnode =  new CJSprite();
//            subnode->initWithTexture(srcSprite->getTexture());
//            subnode->autorelease();
//            
//            ((CJSprite*)subnode)->setDisplayFrame(srcSprite->displayFrame());
//            return subnode;
//        }
        
        return clone;
    }
    
    
    static void stopAllAnimationsWithOutTags(CCNode *node, int exceptTag = -1, ...)
    {
        std::vector<int>* vecExceptTags = new vector<int>;
        va_list args;
        va_start(args,exceptTag);
        while (exceptTag != -1) {
            vecExceptTags->push_back(exceptTag);
            exceptTag = va_arg(args, int);
        }
        va_end(args);

        
        
        
        //node stopAllActions
        for (int j = 0; j < vecExceptTags->size(); j++) {
            
            if (node->getTag() == vecExceptTags->at(j))
            {
                node->stopAllActions();
                break;
            }
            
        }
        
        //return
        if ((CCArray*)node->getChildren() == NULL) {
            vecExceptTags->clear();
            delete vecExceptTags;
            return;
        }
        
  
        
        // children check
        bool isCompared = false;
        for (int i=0; i < ((CCArray*)node->getChildren())->count(); i++)
        {
            CCNode* child =  (CCNode*)((CCArray*)node->getChildren())->objectAtIndex(i);
            
            if (child->getChildrenCount() == 0)
            {
                for (int j = 0; j < vecExceptTags->size(); j++) {
                    if (child->getTag() == vecExceptTags->at(j)) {
                        isCompared = true;
                        break;
                    }
                }
                if(!isCompared)
                    child->stopAllActions();


            }
//            else
//            {
//                
//                stopAllAnimationsWithOutTags(child);
//                
//            }
        }
        
        vecExceptTags->clear();
        delete vecExceptTags;
    }
    
    
    static void objectIsNull(CCNode* pSender)
    {
        pSender = NULL;
    }
    
    
    static CCParticleSystemQuad* addParticle(std::string filename, bool autoRemove = true)
    {
        CCParticleSystemQuad * particle = CCParticleSystemQuad::create(CJUtils::getInstance()->getFilePath("img",filename).c_str());
        particle->setAutoRemoveOnFinish(autoRemove);
        return particle;
    }
 };



#endif
