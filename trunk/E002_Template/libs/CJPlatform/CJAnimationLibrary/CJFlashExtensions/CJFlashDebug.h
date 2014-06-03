//#ifdef COCOS2D_DEBUG

#ifndef __CJ_DEBUG_H__
#define __CJ_DEBUG_H__


#include "cocos2d.h"

#include "CJFlashUtil.h"
#include "CJFlashStdC.h"


namespace CJFlash
{
	struct IRenderBoundingBox
	{
		virtual void drawBoundingBox(){};
	};

	//
	//

	/*************************************************************************
	@
	@	name: CDebugRenderBoundingBox
	@
	@	author: [2013.1.28 CJFlash. YHM]
	@
	@	brief: 바운딩 박스 렌더러
	@		   이 클래스를 현재 렌더링중인 레이어에 붙인뒤 IRenderBoundingBox 를 상속받아
	@		   원하는 형태를 그려주면 된다.
	@
	**************************************************************************/
	class CDebugRenderBoundingBox : public cocos2d::CCNode,
								 public CSingleton<CDebugRenderBoundingBox>
	{
	private:
		typedef std::list<IRenderBoundingBox*>					STL_LIST_DebugRenderShape;
		typedef std::list<IRenderBoundingBox*>::iterator		STL_LIST_ITER_DebugRenderShape;

	private:
		STL_LIST_DebugRenderShape			m_stl_lst_DebugRenderShape;

		GLubyte								m_colorRed;
		GLubyte								m_colorGreen;
		GLubyte								m_colorBlue;
		GLubyte								m_colorAlpha;


	public:
		CDebugRenderBoundingBox();
		~CDebugRenderBoundingBox();

	public:
		virtual void draw();

	public:
		void addRenderBoundBox(IRenderBoundingBox* pObj);
		void removeRenderBoundBox(IRenderBoundingBox* pObj);


	public:
		void setColor4B( GLubyte r, GLubyte g, GLubyte b, GLubyte a )
		{
			m_colorRed = r;
			m_colorGreen = g;
			m_colorBlue = b;
			m_colorAlpha = a;
		}
	};

}	// end of namespace CJFlash


#endif



//#endif