#ifndef __CJ_ANIMATION_SPRITE_H__
#define __CJ_ANIMATION_SPRITE_H__


#include "cocos2d.h"

#include "CJFlashBase.h"

using namespace cocos2d;

/*************************************************************************
@
@	name: CJAnimationSprite
@
@	made by: CJFlash. yhm
@
@	desc: cocos2d-x 의 CCSprite를 상속받은 파생클래스
@		  (CJ 애니메이션에 종속적인 스프라이트 클래스)
@
**************************************************************************/

namespace CJFlash
{

	class CJAnimationSprite : public CJType<cocos2d::CCSprite>
	{
	private:
		const CJFlash::SSpriteSheet*					m_pSheetInfo;		// 해당 스프라이트의 시트 정보
        // 해당 스프라이트의 에니메이션 정보 //added Jonguk.JEON at 2013.05.29
        const CJFlash::SKeyFrameAniData*               m_pKeyFrameAniData;
        // 해당 스프라이트의 모든 프레임에서의 포지션값을 가진 백터 //added Jonguk.JEON at 2013.05.29
        std::vector<CCPoint>                            *m_vecPositions;
        
        
		bool											m_IsLoad;
        
        std::string _myFilePath;
        
        CCPoint                                         deltaPos;


	public:
		CJAnimationSprite(void);
		~CJAnimationSprite(void);


	public:
		virtual void updateFrame( SKeyFrameAniData* pKeyFrameAniData, unsigned int frame, float dt);
		virtual void updateFrame( SKeyFrameAniData* pKeyFrameAniData, unsigned int frame );
        
        virtual void addChild(CCNode *child, int zOrder, int tag);
        virtual void addChild(CCNode *child, int zOrder);
        virtual void addChild(CCNode *child);

	public:
		/**
		desc: !! 아래의 함수들을 임의로 사용하면 안됨
		!! do not use this function...
		**/
		bool preload(bool bIsCommonPath = false);
		void unload(void);

        void setMoveToPosition(CCPoint pt);

		/**
		desc: 시트정보를 세팅하는 함수
		param: pSheet - 세팅할 시트 객체
		**/
		void _setSheet(const CJFlash::SSpriteSheet* pSheet){ m_pSheetInfo = pSheet; }


        /**
         * @author  Jonguk.JEON
         * @brief	에니메이션 정보를 세팅하는 함수.
         * @date    2013.05.29
         **/
        void _setAniData(const CJFlash::SKeyFrameAniData* pAniData){ m_pKeyFrameAniData = pAniData; }
        

	public:

        /**
         * @author  Jonguk.JEON
         * @brief	스프라이트의 모든 프레임의 위치값을 얻는 함수.
         * @date    2013.05.29
         **/
        std::vector<CCPoint>* getVectorSpritePositions();

        
		/**
		desc: 시트정보를 가져옴
		return: 해당 스프라이트의 시트 객체
		**/
		const CJFlash::SSpriteSheet* getSheet(void) const { return m_pSheetInfo; }

		/**
		desc: 스프라이트 시트로부터 스프라이트의 이름을 가져온다.
		return: 현재 스프라이트의 이름
		**/
		const std::string getSpriteName(void) const { return m_pSheetInfo->name; }

		const cocos2d::CCRect getBoundingBox(cocos2d::CCPoint& pos);

	public:
		//void drawBoundingBox(cocos2d::CCPoint& ptPos, float fScaleX, float fScaleY);
	};

}	// end of namespace CJFlashNS


#endif	//__CJ_ANIMATION_SPRITE_H__