//#ifdef COCOS2D_DEBUG

#include "cocos2d.h"

#include "CJFlashDebug.h"


namespace CJFlash
{

	CDebugRenderBoundingBox::CDebugRenderBoundingBox() :
		m_colorRed( 0 ),
		m_colorGreen( 255 ),
		m_colorBlue( 0 ),
		m_colorAlpha( 255 )
	{

	}

	CDebugRenderBoundingBox::~CDebugRenderBoundingBox()
	{
		m_stl_lst_DebugRenderShape.clear();
	}

	void CDebugRenderBoundingBox::addRenderBoundBox( IRenderBoundingBox* pObj )
	{
		m_stl_lst_DebugRenderShape.push_back( pObj );
	}

	void CDebugRenderBoundingBox::removeRenderBoundBox( IRenderBoundingBox* pObj )
	{
		m_stl_lst_DebugRenderShape.remove( pObj );
	}

	void CDebugRenderBoundingBox::draw()
	{
		CCNode::draw();

		//cocos2d::ccColor4B( m_colorRed, m_colorGreen, m_colorBlue, m_colorAlpha );
        
		STL_LIST_ITER_DebugRenderShape iter = m_stl_lst_DebugRenderShape.begin();
		IRenderBoundingBox* pInterface = NULL;
		
		while( iter != m_stl_lst_DebugRenderShape.end() )
		{
			pInterface = *iter;

			pInterface->drawBoundingBox();

			iter++;
		}
	}

}	// end of namespace CJFlash


//#endif