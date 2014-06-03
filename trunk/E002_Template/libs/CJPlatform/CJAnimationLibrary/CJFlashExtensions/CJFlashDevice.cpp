#include "CJFlashDevice.h"



namespace CJFlash
{

	//
	//

	void CDeviceResolution::init( /* unsigned int t_type_resolution */ )
	{
		//type_resolution = t_type_resolution;

		fDeviceWidth = cocos2d::CCDirector::sharedDirector()->getWinSize().width;
		fDeviceHeight = cocos2d::CCDirector::sharedDirector()->getWinSize().height;

		fScaleRatioOfWidth = ((float)fDeviceWidth / 1024.0f);
		fScaleRatioOfHeight = ((float)fDeviceHeight / 768.0f);
	}

	void CDeviceResolution::convertResolutionNode(cocos2d::CCNode* pNode)
	{
		pNode->setScaleX( fScaleRatioOfWidth );
		pNode->setScaleY( fScaleRatioOfHeight );
	}

	void CDeviceResolution::convertResolutionVariable(cocos2d::CCRect* pRect)
	{
		convertResolutionVariable( &pRect->origin );
		convertResolutionVariable( &pRect->size );
	}

	void CDeviceResolution::convertResolutionVariable(cocos2d::CCPoint* pPoint)
	{
		CONVERT_TO_RATIO( pPoint->x, fDeviceWidth, 1024.0f );
		CONVERT_TO_RATIO( pPoint->y, fDeviceHeight, 768.0f );
	}

	void CDeviceResolution::convertResolutionVariable( cocos2d::CCSize* pSize )
	{
		pSize->width = pSize->width * fScaleRatioOfWidth;
		pSize->height = pSize->height * fScaleRatioOfHeight;
	}

	void CDeviceResolution::convertResolutionVariable( float* pValue, unsigned int iType )
	{
		if( iType == DEVICE_WIDTH )
		{
			CONVERT_TO_RATIO( *pValue, fDeviceWidth, 1024.0f );
		}
		else
		{
			CONVERT_TO_RATIO( *pValue, fDeviceHeight, 768.0f );
		}
	}

	//
	//

}	// end of namespace CJFlashNS