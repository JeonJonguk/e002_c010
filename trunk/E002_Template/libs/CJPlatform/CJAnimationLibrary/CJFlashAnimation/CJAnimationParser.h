#ifndef __CJ_ANIMATION_PARSER_H__
#define __CJ_ANIMATION_PARSER_H__

#include "cocos2d.h"


#include "CJHAnimationPreHeader.h"
#include "CJFlashUtil.h"
#include "CJAnimationParserDelegate.h"

#include "../../rapidjson/include/rapidjson/document.h"
#include "../../rapidjson/include/rapidjson/rapidjson.h"


//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////


namespace CJFlash
{

	class CJAnimationDataPool;

	//
	//

        /**  [2013.1.28 CJFlash. YHM]
         desc: XML 파싱 함수
         param:
         - szSheetFileName : 시트 파일 이름
         - szAnimationsFileName : 애니메이션 파일 이름
         **/
        
        rapidjson::Document initParse(const char *pageName);
        
        CJAnimationDataPool* parseJsonAnimation(const char* szSheetFileName, const char* szAnimationsFileName, bool appendFullPath = true );
        
        CJAnimationDataPool* parseXmlAnimation(const char* szSheetFileName, const char* szAnimationsFileName, bool appendFullPath = true );
        
        bool IsStringEqual( const char* str1, const char* str2 );
    
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class _CJSheetDelegator : public cocos2d::CCSAXDelegator
	{
	private:
		CJAnimationDataPool* m_pAniManager;
        
    public:
        CJAnimationParserDelegate* m_parserDelegate;
        
	public:
		_CJSheetDelegator() :
			m_pAniManager( NULL )
		{

		}
		~_CJSheetDelegator()
		{

		}

	public:
        
        void setElement(rapidjson::Document document);
        
//	public:
//        
        virtual void startElement(void *ctx, const char *name, const char **atts);
		virtual void endElement(void *ctx, const char *name){}
		virtual void textHandler(void *ctx, const char *s, int len){}

    public:
        
		void setAnimationManager(CJAnimationDataPool* pManager){ m_pAniManager = pManager; }
        
	};

	//
	//

	class _CJAnimationsDelegator : public cocos2d::CCSAXDelegator
	{
	private:
		CJAnimationDataPool* m_pAniManager;
        
    public:
        CJAnimationParserDelegate* m_parserDelegate;

		CJFlash::SAnimationSheet* m_pAnimationSheet;
		CJFlash::SKeyFrameAniData* m_pKeyFrameData;

		unsigned int		  m_nFrameCnt;

		unsigned int		  m_nDepth;

	public:
		_CJAnimationsDelegator(void) :
			m_pAniManager( NULL )
		{
			m_nFrameCnt = 0;
			m_nDepth = 0;
		}
		~_CJAnimationsDelegator()
		{

		}
        

	public:
        
        void setElement(rapidjson::Document document);
    
//    public:
//        
        virtual void startElement(void *ctx, const char *name, const char **atts);
		virtual void endElement(void *ctx, const char *name);
		virtual void textHandler(void *ctx, const char *s, int len){}
    
    public:
        
		void setAnimationManager(CJAnimationDataPool* pManager){ m_pAniManager = pManager; }

	};

}	// end of namespace CJFlash


#endif //__CJ_ANIMATION_PARSER_H__