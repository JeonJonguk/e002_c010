#include "CJAnimationLibrary.h"



namespace CJFlash
{

	bool initCJAnimationLibrary( void )
	{
		CDeviceResolution::createInstance();
		
		return true;
	}

	void deinitCJAnimationLibrary( void )
	{
		CDeviceResolution::destroyInstance();
		CResourcePathDirector::destroyInstance();
		CDebugRenderBoundingBox::destroyInstance();
        
        CJAllocater::sharedInstance()->dumpCreateObject();
        CJAllocater::destroyInstance();
	}

	const char* CJAnimationLibraryVersion( void )
	{
		return "2.2.1";
	}

}