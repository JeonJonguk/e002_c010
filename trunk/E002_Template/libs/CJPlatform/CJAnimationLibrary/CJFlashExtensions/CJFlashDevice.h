#ifndef __CJ_FLASH_DEVICE_H__
#define __CJ_FLASH_DEVICE_H__


#include "cocos2d.h"

#include "CJFlashUtil.h"


#define CONVERT_TO_RATIO( value, SrcRatio, DstRatio )		value = value * (SrcRatio / DstRatio);

#define DEVICE_WIDTH	1
#define DEVICE_HEIGHT	2


namespace CJFlash
{

	enum 
	{
		kResolution_1024_768,
		kResolution_480_320,
	};

	//
	//

	/*************************************************************************
	@
	@	name: CDeviceResolution
	@
	@	author: [2013.1.28 CJFlash. YHM]
	@
	@	brief: 디바이스 해상도 관리 매니저
	@		   이 클래스를 활용하여 디바이스 해상도 변환에 대응하거나
	@		   원하는 해상도 값으로 변경 할수있다
	@		   CJAnimationLibrary 는 기본적으로 이 클래스를 활용하므로 초기화가 필요하다
	@
	**************************************************************************/
	class CDeviceResolution : public CSingleton<CDeviceResolution>
	{
	protected:
		//unsigned int		type_resolution;

		float				fDeviceWidth;
		float				fDeviceHeight;

		float				fScaleRatioOfWidth;
		float				fScaleRatioOfHeight;

	public:
		CDeviceResolution()
		{
			init();
		}

	public:
		virtual void init(/* unsigned int t_type_resolution */);

		virtual void convertResolutionNode(cocos2d::CCNode* pNode);

		virtual void convertResolutionVariable(cocos2d::CCRect* pRect);
		virtual void convertResolutionVariable(cocos2d::CCPoint* pPoint);
		virtual void convertResolutionVariable(cocos2d::CCSize* pSize);
		virtual void convertResolutionVariable(float* pValue, unsigned int iType);

	public:
		/*************************************************************************
		@
		@	name: 
		@
		@	author: [2012.11.28 CJFlash. YHM]
		@
		@	brief: Don't touch and do not use. 
		@
		**************************************************************************/

		void setForceDeviceResolution(cocos2d::CCSize& size)
		{
			fDeviceWidth = size.width;
			fDeviceHeight = size.height;

			fScaleRatioOfWidth = 1.0f;
			fScaleRatioOfHeight = 1.0f;
		}
	};

}	// end of namespace CJFlashNS

#endif