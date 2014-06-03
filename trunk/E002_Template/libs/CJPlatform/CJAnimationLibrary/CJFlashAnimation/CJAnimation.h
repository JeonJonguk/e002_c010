#ifndef __CJ_ANIMATION_H__
#define __CJ_ANIMATION_H__


#include "cocos2d.h"

#include "CJFlashDebug.h"
#include "CJFlashBase.h"
#include "CJAnimationDataPool.h"

//class CXmlDataPool;

USING_NS_CC;

namespace CJFlash
{
	class CJAnimationSprite;
	class CJAnimation;

	//
	//

	namespace TypeDefineNS
	{
		enum TYPE_EventCall
		{
			kTag_EventCall_Play,
			kTag_EventCall_Stop,
			kTag_EventCall_Pause,
			kTag_EventCall_LastFrame,

			kTag_EventCall_Update,
		};

		enum TYPE_AnimationState
		{
			kState_None,
			kState_PrePlay,
			kState_Play,
			kState_Stop,
			kState_Pause,
		};
	}	// end of namespace TypeDefineNS


    /*************************************************************************
     @
     @	name: CXmlAnimationEventDelegate
     @
     @	made by: CJFlash. yhm
     @
     @	desc: 애니메이션 재생중 특정한 기능을 수행하기 위한 인터페이스 클래스
     @		  이 클래스를 상속받아 다양한 형태의 재생 가능한 클래스를 정의 할수있음
     @
     **************************************************************************/
	class CJAnimationEventDelegator
	{
	public:
		virtual void OnPlay(CJAnimation* pAnimation){}
		virtual void OnStop(CJAnimation* pAnimation){}
		virtual void OnLastFrame(CJAnimation* pAnimation){}
		virtual void OnPause(CJAnimation* pAnimation){}
        
		virtual void OnUpdate(CJAnimation* pAnimation){}
	};
    
	/*************************************************************************
	@
	@	name: CJAnimation
	@
	@	made by: CJFlash. yhm
	@
	@	desc: 실제 애니메이션 정보를 가지고 있는 애니메이션 클래스
	@		  이 클래스와 CJFlashAnimationDelegate 클래스를 활용하여
	@		  애니메이션을 재생할수있다.
	@
	**************************************************************************/
	class CJAnimation : public CJType<cocos2d::CCNode>, public IRenderBoundingBox
	{
    public:
        bool                                        m_bIsCommonPath;
        
	private:
        
		cocos2d::CCNode*							m_pLayer;
		CJAnimationEventDelegator*                   m_pAnimationDelegate;

		std::string									m_strAnimationName;					// 애니메이션 이름


	private:
		unsigned int								m_nCurrentFrame;					// 현재 프레임
		unsigned int								m_nMaxFrame;						// 최대 프레임
        unsigned int                                m_nFramePerSecond;                  // 프레임 속도
        
		bool										m_bIsEventCall;
		bool										m_IsLoad;
		bool										m_bOneFrameCheck;

		CJFlash::STL_LIST_CallBackParam				m_stl_CallbackParam_lst;
        
        std::string                                 m_animation_key;                    //added by JU.JEON 2013.07.02
//        std::string                                 m_datapool_key;                     //added by JU.JEON 2013.07.18
        CJAnimationDataPool*                      _dataPool;

	private:
		bool										m_bRepeatForever;

        int                                         m_nPlayCount;                       //added by JU.JEON 2013.07.01
        unsigned int                                m_nRepeatCount;                     //added by JU.JEON 2013.07.01
        

		TypeDefineNS::TYPE_AnimationState			m_eState;


	private:
		CJFlash::STL_VECTOR_Sprite					m_stl_Sprites_vt;					// 애니메이션에 해당되는 모든 스프라이트 객체를 저장한 벡터
		CJFlash::STL_VECTOR_AnimationData			m_stl_KeyFrameData_vt;				// 애니메이션에 해당되는 모든 키프레임 객체를 저장한 벡터


	public:
		CJAnimation(void);
		virtual ~CJAnimation(void);


	public:
		/**  [2012.11.27 CJFlash. YHM]
		  desc: 함수 오버라이딩
		  param: 
		**/
		virtual void drawBoundingBox(void);


	private:
		/**
		desc: !! 아래의 함수들을 임의로 사용하면 안됨
		!! do not use this function...
		**/
		void _setAnimationName(const std::string animationName){ m_strAnimationName = animationName; }
		void _setMaxFrame(unsigned int nMaxFrame){ m_nMaxFrame = nMaxFrame; }

		void _addSpriteData(CJAnimationSprite* pData);
		void _addKeyFrameAniData(CJFlash::SKeyFrameAniData* pData);

		void _checkCallback(void);
		void _callEventDelegator(const TypeDefineNS::TYPE_EventCall eEventCall);

        
	private:
		void _updateAnimation(float dt);
		void _updateCurrentFrame(void);

//		CC_DEPRECATED_ATTRIBUTE void _updateOneFrameAnimation(float dt);
//		CC_DEPRECATED_ATTRIBUTE void _update(float dt);


	public:
		bool init(CJAnimationEventDelegator* pDelegator, bool bIsEventCall = true);
		void deinit(void);


	public:
        static void flashFrameCallback(cocos2d::CCNode* sender, cocos2d::SEL_CallFuncND pCallFuncND, void* data);
		void addCustomFrameCallback(CCNode *sender, cocos2d::SEL_CallFuncND pCallFuncND, unsigned int nParticularFrame, void* data);

		/**
		desc: 특정한 프레임에 호출되는 콜백함수를 설정
		param: callback - 호출될 콜백 함수
		nParticularFrame - 호출될 특정한 프레임
		pUserData - 호출될때 인자로 들어올 임의의 데이터
		**/
		void addParticularFrameCallback(CCNode *sender, CJFlash::pfCallback callback, unsigned int nParticularFrame, void* pUserData);

		/**
		desc: 추가된 콜백 파라미터를 제거한다.
		param: callback - 제거할 콜백함수의 주소
		**/
		void removeParticularFrameCallback(unsigned int nFrame);
        void removeParticularAllFrame();
        

	public:
		void setAnimationDelegator(CJAnimationEventDelegator* pDelegator){ m_pAnimationDelegate = pDelegator; }
		void setFrame(const unsigned int nFrame);
        void setFramePerSecond(unsigned int nFPS){ m_nFramePerSecond = nFPS; }

        const CJAnimationEventDelegator* getDelegate(void) { return m_pAnimationDelegate; }
		const unsigned int& getFrame(void){ return m_nCurrentFrame; }
		const unsigned int& getMaxFrame(void){ return m_nMaxFrame; }
		const std::string& getName(void){ return m_strAnimationName; }
		const TypeDefineNS::TYPE_AnimationState& getState(void){ return m_eState; }

		const bool& isRepeatForever(void){ return m_bRepeatForever; }

		bool isPrePlay(void){ return m_eState == TypeDefineNS::kState_PrePlay; }
		bool isPlay(void){ return m_eState == TypeDefineNS::kState_Play; }
		bool isStop(void){ return m_eState == TypeDefineNS::kState_Stop; }
		bool isPause(void){ return m_eState == TypeDefineNS::kState_Pause; }
		bool isNone(void){ return m_eState == TypeDefineNS::kState_None; }


        //added by JU.JEON 2013.07.01
    private:
        void _setDataPool(CJAnimationDataPool* dataPool){_dataPool = dataPool;};
    public:
        void setAnimationKey(const char* key){m_animation_key = key;}
        const std::string& getKey(void){return m_animation_key;};
        CJAnimationDataPool* getDataPool(){return _dataPool;};

	public:
		bool checkCollision(cocos2d::CCPoint& pt);

//		CC_DEPRECATED_ATTRIBUTE bool updateOneFrame(void);


	public:
		/*
		@brief	해당 애니메이션의 스프라이트들을 메모리에 로드한다.

		@param	

		@return	성공 여부

		@author	[2012.9.3  CJFlash. YHM]
		*/
		bool preload(void);

		/*
		@brief	해당 애니메이션의 스프라이트들을 메모리에서 제거한다.

		@param	

		@return	

		@author	[2012.9.3  CJFlash. YHM]
		*/
		void unload(void);


    public:
        void runActionWithAllSprite(cocos2d::CCAction* t_pAction);
        
        /**
         desc: 애니메이션으로부터 저장된 스프라이트 객체를 가져옴
         param: strName - 가져올 스프라이트 이름
         return: strName의 스프라이트 객체
         **/
        CJAnimationSprite* getSpriteFromSpriteName(std::string strName);
        
	public:
		/*************************************************************************
		@
		@	name: 
		@
		@	author: [2012.9.3  CJFlash. YHM]
		@
		@	brief: 재생 관련 메소드
		@
		**************************************************************************/


		/*
		@brief	애니메이션을 재생한다.

		@param	nFrame - 재생을 시작할 프레임
		bRepeatForever - 무한반복 재생 여부

		@return	성공 여부

		@author	[2012.9.3  CJFlash. YHM]
		*/
		bool playAnimation(unsigned int nFrame, bool bRepeatForever = false);
        
        
        /*
         @brief	애니메이션을 count 만큼 재생한다.
         
         @param	repeatCount - 재생을 반복할 수
         
         @return	성공 여부
         
         @author	[2013.07.01  Jonguk JEON]
         */
		bool playAnimationRepeatCount(unsigned int repeatCount);
        

		/*
		@brief	애니메이션을 정지시킨다. (프레임은 0으로 초기화)

		@param	IsUnloadSprites - 스프라이트들의 메모리 제거 여부

		@return	

		@author	[2012.9.3  CJFlash. YHM]
		*/
		void stopAnimation(bool IsUnloadSprites = true);

		/*
		@brief	애니메이션을 일시정지시킨다. (프레임은 그대로)

		@param	IsVisible - 일시정지를 시키는데 스프라이트들은 보일것인지

		@return	

		@author	[2012.9.12  CJFlash. YHM]
		*/
		void pauseAnimation(bool IsVisible = true);

		/*
		@brief	애니메이션을 다시 재생시킨다.

		@param	

		@return	성공 여부

		@author	[2012.9.12  CJFlash. YHM]
		*/
		bool resumeAnimation(void);


// #if KINEPIX_BOUNDBOX_RENDER == 1
// 		private:
// 			bool		m_isRenderBoundBox;
// 
// 		public:
// 			void setRenderboundBox(bool isRender){ m_isRenderBoundBox = isRender; }
// #endif
        
        
    public:
        
        CCSize getSizeOfAnimation();
        int getZOrderOfAnimation();
        CCPoint getPositionOfAnimation();
        CCSprite* getSpriteOfAnimation();
        
        
        

		friend class CJAnimationDataPool;
	};

}	// end of namespace CJFlashNS


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////



#endif // __CJ_ANIMATION_H__