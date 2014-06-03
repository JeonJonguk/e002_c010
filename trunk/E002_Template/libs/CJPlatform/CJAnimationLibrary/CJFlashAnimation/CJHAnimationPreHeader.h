#ifndef __CJ_ANIMATION_PRE_HEADER_H__
#define __CJ_ANIMATION_PRE_HEADER_H__



#include <vector>
#include <list>
#include <map>

#include "cocos2d.h"

//#include "..\CJFlashDevice\CJFlashDevice.h"


// #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
// 
// #include "CJFlash_util.h"
// 
// #else
// 
// #include "../CJFlash_util.h"
// 
// #endif


#define NOT_ANI_SHEET			"flash - 애니메이션 시트 정보 없음"
#define NOT_SPR_SHEET			"flash - 스프라이트 시트 정보 없음"


#define	STRING_TO_FLOAT(src)		(float)atof( src )
#define STRING_TO_INT(src)			(int)atoi( src )


#ifndef SAFE_DELETE
#define SAFE_DELETE( object ) if( object ){ delete object;  object = NULL; }
#endif

#define ccp_ex( pt_x, pt_y )		CCDirector::sharedDirector()->convertToGL( ccp( pt_x, pt_y ) )


/*************************************************************************
@
@	name: _gsMyAnimationSheet, _gsMyKeyFrameData, _gsMyKeyFrameAniData, _gsMySpriteSheet, _gsMyCallbackParam
@
@	made by: CJFlash. yhm
@
@	desc: _gsMyAnimationSheet - 애니메이션의 시트 구조체이며 animations.xml / animations.json에 추출된 애니메이션의 정보가 들어가있는 구조체이다
@
@		  _gsMyKeyFrameData - 1프레임당 데이터들이 저장되는 구조체
@							  위치값, 스케일값, 회전값 등등 1 프레임의 모든 정보가 들어가있다
@							  이 구조체의 객체 하나당 하나의 프레임 정보가 들어가있다
@
@		  _gsMyKeyFrameAniData - _gsMyKeyFrameData 들의 정보들을 저장해놓은 구조체이며
@								 스프라이트 하나의 _gsMyKeyFrameData 들이 저장된 구조체이다
@
@		  _gsMySpriteSheet - 스프라이트 하나당 존재하는 스프라이트의 정보를 담는 구조체
@							sheets.xml / sheets.json 파일에서 파싱된 데이터 하나당 하나의 구조체이다
@
@		  _gsMyCallbackParam - 특정한 프레임에 호출될 콜백 함수를 정의할때 필요한 정보들을 담는 구조체이다
@
**************************************************************************/


namespace CJFlash
{
	class CJAnimationSprite;
	class CJAnimation;

	//
	//

	struct SAnimationSheet
	{
		std::string				strAniName;		// 애니메이션 이름
		unsigned int			nFrameCount;	// 애니메이션의 총 프레임 수
        
        SAnimationSheet()
        {
            strAniName = "";
            nFrameCount = 0;
        }
	};

	typedef		std::vector<SAnimationSheet*>					STL_VECTOR_AnimationSheet;
	typedef		std::vector<SAnimationSheet*>::iterator			STL_VECTOR_ITER_AnimationSheet;


	struct SKeyFrameData
	{
		unsigned int			nKeyFrameIndex;			// 프레임 인덱스
		cocos2d::CCPoint		KeyFramePosition;		// 위치 값
		cocos2d::CCPoint		KeyFrameScale;			// 스케일 값
		float					fKeyFrameAlpha;			// 알파 값
		float					fKeyFrameRotation;		// 회전 값

		SKeyFrameData(void)
		{
			KeyFramePosition = ccp( 0.0f, 0.0f );
			KeyFrameScale = ccp( 1.0f, 1.0f );
			fKeyFrameRotation = 0.0f;
			fKeyFrameAlpha = 255.0f;
			nKeyFrameIndex = 0;
		}

	};

	typedef		std::vector<SKeyFrameData*>					STL_VECTOR_KeyFrameData;
	typedef		std::vector<SKeyFrameData*>::iterator		STL_VECTOR_ITER_KeyFrameData;


	///////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////


	struct SKeyFrameAniData
	{
		STL_VECTOR_KeyFrameData		stl_KeyFrame_vt;		// 키프레임 데이터들

		unsigned int			nMaxFrame;				// 해당 스프라이트의 최대 프레임값
		std::string				strAnimationName;		// 자신이 속한 애니메이션의 이름
		std::string				strSpriteName;			// 자신의 스프라이트 이름

		SKeyFrameAniData(void)
		{
			nMaxFrame = 0;
			strAnimationName = "";
			strSpriteName = "";
		}
		~SKeyFrameAniData(void)
		{
			STL_VECTOR_ITER_KeyFrameData iter = stl_KeyFrame_vt.begin();
			SKeyFrameData* pData = NULL;
			while( iter != stl_KeyFrame_vt.end() )
			{
				pData = *iter;

				iter++;

				SAFE_DELETE( pData );
			}
			stl_KeyFrame_vt.clear();
		}

	};

	typedef		std::vector<SKeyFrameAniData*>					STL_VECTOR_AnimationData;
	typedef		std::vector<SKeyFrameAniData*>::iterator		STL_VECTOR_ITER_AnimationData;



	///////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////


	struct SSpriteSheet
	{
		std::string name;						// 인스턴스 이름
		std::string filePath;					// 리소스 파일 경로

		unsigned int nWidth;					// 이미지 넓이
		unsigned int nHeight;					// 이미니 높이

		cocos2d::CCPoint registrationPoint;		// 인스턴스의 중심값

		unsigned int zIndex;					// Z 값


		SSpriteSheet(void)
		{
			name = "";
			filePath = "";

			nWidth = 0;
			nHeight = 0;

			registrationPoint.x = 0.0f;
			registrationPoint.y = 0.0f;

			zIndex = 0;
		}

	};

	typedef		std::vector<SSpriteSheet*>				STL_VECTOR_SpriteSheet;
	typedef		std::vector<SSpriteSheet*>::iterator	STL_VECTOR_ITER_SpriteSheet;


	///////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////


	typedef void (*pfCallback)(cocos2d::CCNode* sender, cocos2d::SEL_CallFuncND pCallFuncND, void* data);
	struct SCallbackParam
	{
		SCallbackParam(cocos2d::CCNode* _sender, cocos2d::SEL_CallFuncND t_pCallFuncND, unsigned int t_nFrame, pfCallback t_pParticularFrameCallback, void* data)
		{
            sender = _sender;
			pCallFuncND = t_pCallFuncND;
			nFrame = t_nFrame;
			pParticularFrameCallback = t_pParticularFrameCallback;
            userData = data;
            
		}
        cocos2d::CCNode*            sender;                         //added by JU.JEON
		cocos2d::SEL_CallFuncND		pCallFuncND;					// 콜백될때 인자로 들어올 사용자 임의 데이터
		unsigned int                nFrame;                         // 콜백될 프레임
		pfCallback                  pParticularFrameCallback;       // 콜백될 함수
        void*                       userData;
	};
    
	typedef		std::list<SCallbackParam>				STL_LIST_CallBackParam;
	typedef		std::list<SCallbackParam>::iterator	STL_LIST_ITER_CallBackParam;



	///////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////



	typedef		std::vector<CJFlash::CJAnimationSprite*>							STL_VECTOR_Sprite;
	typedef		std::vector<CJFlash::CJAnimationSprite*>::iterator				STL_VECTOR_ITER_Sprite;


}	// end of namespace CJFlashNS
								 

#endif	//__CJH_ANIMATION_PRE_HEADER_H__