/*@ 
	Copyrightⓒ. 2012. KINEPIX. All Rights Reserved
	Made by. KINEPIX


	Warning. Compiled With a compiler that supports C++11
S
	------------------------------------------------------------------------------
	CJFlash Library.
		- version 2.2.1

		- Add library list 
				- CJFlashBase
						- Macro
						- StdC

				- CJFlashExtensions
						- DeviceResolutionManager
						- DebugUtility
						- ResourcePathDirector

				- CJFlashUtil
						- SmartPointer
						- Singleton

				- CJFlashAnimation
						- XmlParser
						- XmlDataPool
						- XmlSprite
						- XmlAnimation

				- CJPsd
						- XmlParser
						- XmlPsdDataPool
						- XmlPsdSprite
						- XmlPsdAnimationSprite
						- XmlPsd

	----------------------------------------------------------------------------
@*/


#ifndef __CJ_H_KINEPIX_LIBRARY_H__
#define __CJ_H_KINEPIX_LIBRARY_H__



//#include "CJFlashPlatform/CJPlatformInterface.h"
#include "CJFlashBase.h"
#include "CJFlashUtil.h"
#include "CJFlashExtension.h"
#include "CJHAnimation.h"

using namespace CJFlash;

namespace CJFlash
{

	/**  [2013.2.12 CJFlash. YHM]
	  desc: 키네픽스 라이브러리 초기화
	  param: 
	**/
	bool initCJAnimationLibrary( void );

	/**  [2013.2.12 CJFlash. YHM]
	  desc: 키네픽스 라이브러리 해제
	  param: 
	**/
	void deinitCJAnimationLibrary( void );

	/**  [2013.2.12 CJFlash. YHM]
	  desc: 키네픽스 라이브러리 버전 체크
	  param: 
	  return: 키네픽스 라이브러리 버전 string
	**/
	const char* CJAnimationLibraryVersion( void );
    
}


#endif // !__CJ_H_KINEPIX_LIBRARY_H__



/*@ 
	Release-Note

	[2012/06/12] version 1.0.0	
	- 최초 릴리즈

	-----------------------------------------------------------------------------

	[2012/08/03] version 1.0.2
	- Flash-XmlViewer 용도에 맞게 일부 코어부분 수정
	- 코어부분 수정한곳에 viewer 종속적인부분 한단계 추상화

	----------------------------------------------------------------------------

	[2012/10/05] version 1.1.2
	- XmlAnimation 인터페이스 변경

	----------------------------------------------------------------------------

	[2012/12/16] version 2.0.0
	- XmlAnimation  관련 클래스 전체 수정
	- CJFlashBase 추가
	- CJFlashExtensions 추가
	- CJFlashUtil 추가
	- CJFlashAnimation 추가
	- CJPsd 추가
	- 라이브러리 통합
	- 2.0.0 버전 XmlViewer 개발

	----------------------------------------------------------------------------
	
	[2013/01/28] version 2.1.1
	- XmlAnimation, XmlParser 수정

	----------------------------------------------------------------------------

	[2013/03/04] version 2.2.1
	- XmlPsd modify
	- XmlPsdDataPool modify
	- XmlPsdAnimationSprite add
	- XmlPsdExtension Set add
	- PsdXmlExtensionGenerator Set add
@*/