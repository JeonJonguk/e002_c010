#ifndef __CJ_ANIMATION_DATA_POOL_H__
#define __CJ_ANIMATION_DATA_POOL_H__

#include "cocos2d.h"

#include "CJHAnimationPreHeader.h"
#include "CJFlashBase.h"

#include "CJAnimationLibrary.h"

namespace CJFlash
{
	class CJAnimationSprite;
	class CJAnimation;

	//
	//

	/*************************************************************************
	@
	@	name: CJAnimationDataPool
	@
	@	made by: CJFlash. YHM
	@
	@	desc: (KF -> KeyFrame) KFAni를 관리하는 매니지먼트 클래스
	@		  XML/JSON을 파싱한후 저장한 객체들을 관리하며
	@		  애니메이션을 재생 or 정지 또는 여러가지 기능을 하는 클래스다	  
	@		  XML/JSON을 파싱하여 나온 모든 애니메이션들은 이 클래스를 이용하여
	@		  재생한다.
	@			
	@		  !! 파싱된 파일마다 n:n 의 CJAnimationDataPool 객체가 생성된다.
	@
	@	1차 수정 ----------------------------------
	@		  해당 클래스를 이용하여 Animation을 재생하는 기능을 없애고
	@		  CJAnimation 클래스와 function 클래스를 이용하여 재생하게 만듬
	@
	@	2차 수정 ----------------------------------
	@		  cocos2dx의 MutableArray를 사용하던 방식을 표준 템플릿 라이브러리인
	@		  vector로 변경
	@
	@	3차 수정 ----------------------------------
	@		  CJAnimationDataPool 클래스는 sheets.xml / sheets.json 와 animations.xml / animations.json 파일에서 파싱된
	@		  정보만 가지고 있게 변경
	@		  (애니메이션 재생, 정지 같은 기능들은 제공안함)
	@
	@	4차 수정 ----------------------------------
	@		  클래스 이름이 gcAnimationManager 에서 CJAnimationDataPool 로 바뀜
	@
	@	5차 수정 ----------------------------------
	@		  저장 방식을 vector 에서 multimap 으로 변경
	@
	**************************************************************************/
	class CJAnimationDataPool : public CJType<cocos2d::CCObject>
    {
	private:
		/*************************************************************************
		@
		@	name: 
		@
		@	author: [2012.8.31  CJFlash. YHM]
		@
		@	brief: 기존 STL vector 방식에서 STL map 방식으로 변경 
		@
		**************************************************************************/
		typedef std::multimap<std::string, CJFlash::SAnimationSheet*>		STL_MULTIMAP_ANIMATIONSHEETS;
		typedef std::multimap<std::string, CJFlash::SSpriteSheet*>			STL_MULTIMAP_SPRITESHEETS;
		typedef std::multimap<std::string, CJFlash::SKeyFrameAniData*>		STL_MULTIMAP_KEYFRAMEANIDATAS;
        typedef std::multimap<std::string, CJFlash::CJAnimation*>           STL_MULTIMAP_ANIMATIONS;

		STL_MULTIMAP_ANIMATIONSHEETS			m_stl_mmap_AnimationSheet;
		STL_MULTIMAP_SPRITESHEETS				m_stl_mmap_SpriteSheet;
		STL_MULTIMAP_KEYFRAMEANIDATAS			m_stl_mmap_KeyFrameSheet;
        
        
        //added by Dongjin 2014.01.29
        STL_MULTIMAP_ANIMATIONS                 m_stl_mmap_Animations;

        std::vector<CJAnimation*>* pStl_vt_CJAni;
        
	public:
		CJAnimationDataPool(void);
		~CJAnimationDataPool(void);


	public:
		/**
		desc: !! 아래의 함수들을 임의로 사용하면 안됨
		!! do not use this function...
		**/
		bool _addSpriteSheetData( CJFlash::SSpriteSheet* pSheet );
		bool _addAnimationSheetData( CJFlash::SAnimationSheet* pSheet );
		bool _addKeyFrameAniData( CJFlash::SKeyFrameAniData* pKeyFrameAniData);

        bool _mIsCommon;
	public:
		bool setup(void);


	public:
		unsigned int getNumberOfAnimation(void){ return m_stl_mmap_AnimationSheet.size(); }



	public:
		/**
		desc: 스프라이트 이름으로 스프라이트 시트 데이터를 가져옴
		param: spriteName - 가져올 스프라이트 시트의 스프라이트 이름
		**/
		const CJFlash::SSpriteSheet* getSpriteSheetFromSpriteName(std::string spriteName);

		/**
		desc: 애니메이션 이름으로 애니메이션 시트 데이터를 가져옴
		param: aniName - 가져올 애니메이션 시트의 애니메이션 이름
		**/
		const CJFlash::SAnimationSheet* getAnimationSheetFromAnimationName(std::string aniName);

	public:
        
        //        CJAnimationSprite* createSpriteObjectFromKeyframeData(SKeyFrameAniData* pKeyFrameAniData);
        //        const SKeyFrameAniData* getSpriteFrameAniDataFromSpriteName( std::string spriteName );
        
        
        
        
		/**
		desc: 스프라이트 이름으로 새로운 스프라이트 객체를 생성한다
		param: spriteName - 생성할 스프라이트의 이름
		**/
		CJAnimationSprite* createSpriteObjectFromSpriteName(std::string spriteName);

		/**
		desc: 애니메이션 이름으로 새로운 애니메이션 객체를 생성하고 구성한다.
		param: aniName - 생성할 애니메이션의 이름
		**/
		CJAnimation* createAnimationObjectFromAnimationName(std::string aniName);
        

        
        //added by Dongjin 2014.01.29
        
        /**  [2012.10.17 CJFlash. YHM]
         desc: xml/json내의 애니메이션 객체를 전부 생성
         param: pStl_vt_CJAni - CJ animation 객체를 담을 stl vector 컨테이너 포인터
         **/
        void createAllAnimations();

		std::vector<CJAnimation*>* getAllAnimations();
        std::vector<CJAnimation*>* getAllAnimationsAndCreate();
        
        CJAnimation* getAnimationFromAnimationName(std::string aniName);
        CJAnimation* getAnimationFromAnimationKey(std::string aniKey);
        
        int getAnimationCount();
        

        
        
        //added by JU.JEON 2013.07.18
    private:
        std::string _dataPoolKey;
    public:
        void setDataPoolKey(const std::string dataPoolKey){ _dataPoolKey = dataPoolKey; }
        const std::string& getKey(void){return _dataPoolKey;};
        
	};

}	// end of namespace CJFlashNS


// document-----------------------------------------------------------------
//
//  [2012/6/20/ CJFlash. YHM]
// 1. 이 클래스를 직접적으로 사용하는것은 위험해보인다.
//    후에 인터페이스 클래스를 만들어서 사용하는형태로 바꿔야 함
//
//  [2012/6/27/ CJFlash. YHM]
// 1. 2012/6/20 - 1번 사항 적용 완료
//




#endif //__CJ_ANIMATION_DATA_POOL_H__