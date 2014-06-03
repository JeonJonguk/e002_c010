#ifndef __CJ_LAYOUT_H__
#define __CJ_LAYOUT_H__


#include "cocos2d.h"
#include "CJFlashUtil.h"


#define CJ_OBJ_DELETE(pObj)     if( m_pAnimation != NULL ) \
                                { \
                                    if( pObj->isManaged() ) \
                                        pObj->release(); \
                                    else \
                                        CJ_SAFE_DELETE( pObj ); \
                                }

namespace CJFlash
{
    
    class CJAllocater : public CSingleton<CJAllocater>
    {
    private:
        unsigned int                m_nAllocObjects;
        
        
    public:
        CJAllocater() :
            m_nAllocObjects( 0 )
        {}
        
    public:
        void notifyCreateObject(void)
        {
            ++m_nAllocObjects;
        }
        void notifyDestroyObject(void)
        {
            CCAssert( m_nAllocObjects, "CJAllocater destroy : alloc object zero" );
            --m_nAllocObjects;
        }
        unsigned int& dumpCreateObject(void)
        {
            cocos2d::CCLog( "CJFlash library alloc number of object: %d", m_nAllocObjects );
            
            return m_nAllocObjects;
        }
        
    public:
        template<class allocT>
        static allocT* create(bool isManaged = true)
        {
            allocT* obj = new allocT();
            
            if( isManaged )
            {
                obj->autorelease();
                obj->retain();
            }
            
            obj->setManaged( isManaged );
            
            return obj;
        }
        
        //
        //
        
//        template<class allocT>
//        static allocT* create()
//        {
//            allocT* obj = new allocT();
//            obj->autorelease();
//            obj->retain();
//            
//            return obj;
//        }
        
        template<class allocT, class arg_one>
        static allocT* create(arg_one t_arg1 )
        {
            allocT* obj = new allocT( t_arg1 );
            obj->autorelease();
            obj->retain();
            
            return obj;
        }
    };
    
    /////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
    // next class imp
    /////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////
    
    class CJBaseObject
    {
    private:
        bool              m_isManaged;
        
    protected:
        CJBaseObject() :
            m_isManaged( true )
        {
            CJAllocater::sharedInstance()->notifyCreateObject();
        }
        ~CJBaseObject()
        {
            CJAllocater::sharedInstance()->notifyDestroyObject();
        }
        
    public:
        void setManaged(bool isManaged){ m_isManaged = isManaged; }
        bool& isManaged(void){ return m_isManaged; }
        
    public:
        virtual bool preload(void){}
        virtual void unload(void){}
        
    };
    
    ////////////////////
    
    
    
    
//    class CJObject : public cocos2d::CCObject,
//    public CJBaseObject
//    {
//    protected:
//        CJObject(){}
//        ~CJObject(){}
//    };
//    
//    class CJSprite : public cocos2d::CCSprite,
//    public CJBaseObject
//    {
//    protected:
//        CJSprite(){}
//        ~CJSprite(){}
//    };
//    
//    class CJLayer : public cocos2d::CCLayer,
//    public CJBaseObject
//    {
//    protected:
//        CJLayer(){}
//        ~CJLayer(){}
//    };
//    
//    class CJMenu : public cocos2d::CCMenu,
//    public CJBaseObject
//    {
//    protected:
//        CJMenu(){}
//        ~CJMenu(){}
//    };
//    
//    class CJNode : public cocos2d::CCNode,
//    public CJBaseObject
//    {
//    protected:
//        CJNode(){}
//        ~CJNode(){}
//    };
    
    
    template<class cocos2d_class>
    class CJType : public cocos2d_class,
                   public CJBaseObject
    {
    protected:
        CJType(){}
        
    public:
        ~CJType(){}
        
        
        friend class CJAllocater;
    };
    
    
    
    
    /////////////////////
    
    
	struct __CJSRenderObject
	{
		unsigned int				nZorder;
		cocos2d::CCNode*			pRenderNode;

		__CJSRenderObject(unsigned int t_nZorder, cocos2d::CCNode* t_pRenderNode) :
			nZorder( t_nZorder ),
			pRenderNode( t_pRenderNode )
		{

		}
	};
    
    /////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
    // next class imp
    /////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////
    
	class CLayoutConfig
	{
	private:
		std::vector<__CJSRenderObject>		m_stl_vt_renderObj;


    public:
        CLayoutConfig()
        {
            clearConfig();
        }
        

	public:
		void addRenderObjectConfig(cocos2d::CCNode* t_pRenderNode, unsigned int nZorder)
		{
			__CJSRenderObject obj( nZorder, t_pRenderNode );

			m_stl_vt_renderObj.push_back( obj );
		}

		void clearConfig()
		{
			m_stl_vt_renderObj.clear();
		}

		const std::vector<__CJSRenderObject>& getData() const { return m_stl_vt_renderObj; }
	};
	

    /////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
    // next class imp
    /////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////


	class CLayout : public CJType<cocos2d::CCLayer>
	{
	private:


    protected:
        CLayout(){}
		virtual ~CLayout(){}


	public:
//        static CLayout* create()
//        {
//            CLayout* pLayout = new CLayout;
//            pLayout->autorelease();
//            pLayout->retain();
//            
//            return pLayout;
//        }
        
		bool composeLayout(CLayoutConfig* t_pLayoutConfig)
		{
			const std::vector<__CJSRenderObject> data = t_pLayoutConfig->getData();

			for( unsigned int i = 0; i < data.size(); i++ )//__CJSRenderObject i : data )
			{
				this->addChild( data[i].pRenderNode, data[i].nZorder );
			}

			return true;
		}

        friend class CJAllocater;
	};

}


#endif // !__CJ_LAYOUT_H__
