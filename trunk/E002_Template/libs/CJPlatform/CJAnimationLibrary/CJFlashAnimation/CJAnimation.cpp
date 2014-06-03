
#include "CJAnimation.h"

#include "CJHAnimationPreHeader.h"
#include "CJAnimationSprite.h"
#include "CJFlashDevice.h"

using namespace cocos2d;

namespace CJFlash
{

	CJAnimation::CJAnimation(void)
	{
        m_bIsCommonPath = false;
        
		m_pAnimationDelegate = NULL;
		m_pLayer = NULL;

		m_nCurrentFrame = 0;
		m_nMaxFrame = 0;
        m_nFramePerSecond = 40;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        m_nFramePerSecond = 37.8f;
#endif
        
        
		m_bIsEventCall = false;
		m_IsLoad = false;

		m_bRepeatForever = false;
        
        m_nPlayCount = 0;
        m_nRepeatCount = 1;

		m_eState = TypeDefineNS::kState_Stop;
	}

	CJAnimation::~CJAnimation(void)
	{
		deinit();

		removeAllChildrenWithCleanup( true );

		STL_VECTOR_ITER_Sprite iter = m_stl_Sprites_vt.begin();
		CJAnimationSprite* pSprite = NULL;
		while( iter != m_stl_Sprites_vt.end() )
		{
			pSprite = *iter;

			iter++;

			//CC_ASSERT( pSprite->isSingleReference() );
			CC_SAFE_DELETE( pSprite );	
		}

		m_stl_KeyFrameData_vt.clear();
		m_stl_Sprites_vt.clear();


		//
		m_stl_CallbackParam_lst.clear();
        
        
        

		//

		//CC_SAFE_DELETE( m_pAnimationDelegate );

		m_pLayer = NULL;
	}

	bool CJAnimation::init( CJAnimationEventDelegator* pDelegator, bool bIsEventCall /*= true*/ )
	{
		if( pDelegator == NULL )
			return false;

		m_bIsEventCall = bIsEventCall;

		setAnimationDelegator( pDelegator );

//		setAnchorPoint( ccp( 0.0f, 0.0f ) );
//		setPosition( ccp( 0.0f, 0.0f ) );

		//this->schedule( schedule_selector( CJAnimation::_update ), 1.0f / 60.0f );

		return true;
	}

	void CJAnimation::deinit( void )
	{
		unload();

        // 2.0
		CCDirector::sharedDirector()->getScheduler()->unscheduleSelector( schedule_selector( CJAnimation::_updateAnimation ), this );
        
        // fix to 1.0
//        CCScheduler::sharedScheduler()->unscheduleSelector( schedule_selector( CJAnimation::_updateAnimation ), this );
        
		//his->unschedule( schedule_selector( CJAnimation::_updateAnimation ) );
		//this->unschedule( schedule_selector( CJAnimation::_update ) );
	}


	void CJAnimation::_addKeyFrameAniData( SKeyFrameAniData* pData )
	{
		m_stl_KeyFrameData_vt.push_back( pData );
	}

	void CJAnimation::_addSpriteData( CJAnimationSprite* pData )
	{
		m_stl_Sprites_vt.push_back( pData );
	}



	/*************************************************************************
	@
	@	name: 
	@
	@	author: [2012.8.31  CJFlash. YHM]
	@
	@	brief: FrameCallback ∞¸∑√ «‘ºˆ ¡§¿«∫Œ
	@
	**************************************************************************/
	
    void CJAnimation::_checkCallback( void )
	{
		STL_LIST_ITER_CallBackParam iter = m_stl_CallbackParam_lst.begin();
        
		while( iter != m_stl_CallbackParam_lst.end() )
		{
			SCallbackParam pCallbackParam = *iter;
            
			if( pCallbackParam.nFrame == m_nCurrentFrame )
				pCallbackParam.pParticularFrameCallback( pCallbackParam.sender, pCallbackParam.pCallFuncND, pCallbackParam.userData );
            
			iter++;
		}
	}
    

	void CJAnimation::_callEventDelegator( const TypeDefineNS::TYPE_EventCall eEventCall )
	{
		if( !m_bIsEventCall || m_pAnimationDelegate == NULL )
			return ;

		switch( eEventCall )
		{
		case TypeDefineNS::kTag_EventCall_Play :
			m_pAnimationDelegate->OnPlay( this );
			break;

		case TypeDefineNS::kTag_EventCall_Stop :
			m_pAnimationDelegate->OnStop( this );
			break;

		case TypeDefineNS::kTag_EventCall_Pause :
			m_pAnimationDelegate->OnPause( this );
			break;

		case TypeDefineNS::kTag_EventCall_LastFrame :
			m_pAnimationDelegate->OnLastFrame( this );
			break;

		case TypeDefineNS::kTag_EventCall_Update :
			m_pAnimationDelegate->OnUpdate( this );
			break;
		}
	}


    void CJAnimation::flashFrameCallback(cocos2d::CCNode* sender, cocos2d::SEL_CallFuncND pCallFuncND, void* data)
    {
        sender->runAction(CCCallFuncND::create(sender, pCallFuncND, (void*)data));
    }
    
	void CJAnimation::addCustomFrameCallback( CCNode *sender, cocos2d::SEL_CallFuncND pCallFuncND, unsigned int nParticularFrame, void* data)
	{
		m_stl_CallbackParam_lst.push_back( SCallbackParam(sender, pCallFuncND, nParticularFrame, flashFrameCallback, data));
	}

    
	void CJAnimation::addParticularFrameCallback(CCNode *sender, pfCallback callback, unsigned int nParticularFrame, void* pUserData )
	{
		m_stl_CallbackParam_lst.push_back( SCallbackParam( sender, NULL, nParticularFrame, callback, pUserData ) );
	}

	void CJAnimation::removeParticularFrameCallback( unsigned int nFrame )
	{
		STL_LIST_ITER_CallBackParam iter = m_stl_CallbackParam_lst.begin();

		while( iter != m_stl_CallbackParam_lst.end() )
		{
			SCallbackParam pParam = *iter;

			if( pParam.nFrame == nFrame )
			{
				m_stl_CallbackParam_lst.erase( iter );

				return ;
			}

			iter++;
		}
	}
    
    void CJAnimation::removeParticularAllFrame()
	{
		STL_LIST_ITER_CallBackParam iter = m_stl_CallbackParam_lst.begin();
        
		while( iter != m_stl_CallbackParam_lst.end() )
		{
            m_stl_CallbackParam_lst.erase( iter );
			iter++;
		}
	}
    

	void CJAnimation::setFrame( const unsigned int nFrame )
	{
		m_nCurrentFrame = nFrame;
		
		_updateCurrentFrame();

		//updateOneFrame();
	}


	bool CJAnimation::checkCollision( cocos2d::CCPoint& pt )
	{
		CCRect bd;
		CCPoint pos;

		pos = CCNode::getPosition();
		for( unsigned int i = 0; i < m_stl_Sprites_vt.size(); i++ )
		{
			bd = m_stl_Sprites_vt[i]->getBoundingBox( pos );

            // cocos2d ver 2.0 code
			if( bd.containsPoint( pt ) )
			{
				return true;
			}
            
            // fix cocos2d ver 1.0 code
//            if( CCRect::CCRectContainsPoint( bd, pt ) )
//            {
//                return true;
//            }
		}

		return false;
	}

	bool CJAnimation::preload( void )
	{
		if( !m_IsLoad )
		{
			for( unsigned int i = 0; i < m_stl_Sprites_vt.size(); i++ )
			{
				m_stl_Sprites_vt[i]->preload(m_bIsCommonPath);
                m_stl_Sprites_vt[i]->updateFrame( m_stl_KeyFrameData_vt[i], 0);
                
                this->addChild( m_stl_Sprites_vt[i], m_stl_Sprites_vt[i]->getSheet()->zIndex );
			}
            
            CCPoint movePos = getPositionOfAnimation();
            CCSize aniSize = getSizeOfAnimation();
            
            for( unsigned int i = 0; i < m_stl_Sprites_vt.size(); i++ )
			{
                m_stl_Sprites_vt[i]->setMoveToPosition(ccp(-movePos.x, -movePos.y));

			}
            
            this->setContentSize(aniSize);
            this->setAnchorPoint(ccp(0.5f, 0.5f));
            this->setPosition(ccp(movePos.x + this->getContentSize().width/2 , movePos.y + this->getContentSize().height/2));
            
//            CCLog("ANC:%f, %f", this->getAnchorPoint().x, this->getAnchorPoint().y);
//            CCLog("POS:%f, %f", this->getPosition().x, this->getPosition().y);
//            CCLog("CON:%f, %f", this->getContentSize().width, this->getContentSize().height);
            
			m_IsLoad = true;
		}

		return true;
	}

	void CJAnimation::unload( void )
	{
		if( m_IsLoad )
		{
			for( unsigned int i = 0; i < m_stl_Sprites_vt.size(); i++ )
			{
                m_stl_Sprites_vt[i]->stopAllActions();
				m_stl_Sprites_vt[i]->unload();
                
				this->removeChild( m_stl_Sprites_vt[i], false );
			}

			m_IsLoad = false;
		}
	}

	bool CJAnimation::playAnimation( unsigned int nFrame, bool bRepeatForever /*= false*/ )
	{
// 		if( !m_pLayer )
// 			return false;

        if (m_eState == TypeDefineNS::kState_PrePlay) {
            return false;
        }
        
		if( !this->preload() )
			return false;

		m_bRepeatForever = bRepeatForever;

		setFrame( nFrame );
		setVisible( true );

		//this->setFrame( nFrame );

		//if( !this->isScheduled( schedule_selector( CJAnimation::_updateAnimation ) ) )
        
        CCScheduler* pScheduler = NULL;
        
        // cocos2d_version 1.0 code
        //pScheduler = CCScheduler::sharedScheduler();
        
        // cocos2d_version 2.0 code
        pScheduler = CCDirector::sharedDirector()->getScheduler();
        
		pScheduler->unscheduleSelector( schedule_selector( CJAnimation::_updateAnimation ), this );
		pScheduler->scheduleSelector( schedule_selector( CJAnimation::_updateAnimation ), this, 1.0f / (float)m_nFramePerSecond, false );
        
// 		this->unschedule( schedule_selector( CJAnimation::_updateAnimation  ) );
// 		this->schedule( schedule_selector( CJAnimation::_updateAnimation ), 1.0f / 60.0f );

		m_eState = TypeDefineNS::kState_PrePlay;

		return true;
	}


    bool CJAnimation::playAnimationRepeatCount(unsigned int repeatCount)
    {
        m_nRepeatCount = repeatCount;
        return this->playAnimation(0);
    }
    
    
	void CJAnimation::stopAnimation( bool IsUnloadSprites /*= true*/ )
	{
        
        if (m_eState == TypeDefineNS::kState_Stop) { //added by JU.JEON 2013.07.01
            return;
        }
        
        m_nRepeatCount = 1; //added by JU.JEON 2013.07.01
        m_nPlayCount = 0;   //added by JU.JEON 2013.07.01
        
		setVisible( !IsUnloadSprites ); //modified by Jonguk JEON 2013.07.01
        
		setFrame( 0 );
        

		if( IsUnloadSprites )
			this->unload();

		m_eState = TypeDefineNS::kState_Stop;
	}

	void CJAnimation::pauseAnimation( bool IsVisible /*= true*/ )
	{
		this->setVisible( IsVisible );

		m_eState = TypeDefineNS::kState_Pause;
	}

	bool CJAnimation::resumeAnimation( void )
	{
		bool bRet = false;

		this->setVisible( true );

        //added by JU.JEON 2013.07.01
        if (m_nRepeatCount > 1) {
            bRet = playAnimationRepeatCount(m_nRepeatCount);
        }else{
            bRet = playAnimation( this->getFrame(), this->isRepeatForever() );
        }
        

        
		return bRet;
	}

	void CJAnimation::_updateAnimation( float dt )
	{
		_checkCallback();		// ƒ›πÈ √º≈©

        CCScheduler* pScheduler = NULL;
        
        // cocos2d_version 1.0 code
        //pScheduler = CCScheduler::sharedScheduler();
        
        // cocos2d_version 2.0 code
        pScheduler = CCDirector::sharedDirector()->getScheduler();
        
		switch( m_eState )
		{
            case TypeDefineNS::kState_None :
                return ;
                
            case TypeDefineNS::kState_PrePlay :
                _callEventDelegator( TypeDefineNS::kTag_EventCall_Play );
                m_eState = TypeDefineNS::kState_Play;
                break;
                
            case TypeDefineNS::kState_Stop :
                _callEventDelegator( TypeDefineNS::kTag_EventCall_Stop );
                pScheduler->unscheduleSelector( schedule_selector( CJAnimation::_updateAnimation ), this );
                m_eState = TypeDefineNS::kState_None;
                
                return ;
                
            case TypeDefineNS::kState_Pause :
                _callEventDelegator( TypeDefineNS::kTag_EventCall_Pause );
                //CCDirector::sharedDirector()->getScheduler()->unscheduleSelector( schedule_selector( CJAnimation::_updateAnimation ), this );
                
//                m_eState = TypeDefineNS::kState_None;
                
                return ;
                
            case TypeDefineNS::kState_Play:
                break;
		}

		if( m_eState == TypeDefineNS::kState_Play )
		{
			if( m_nCurrentFrame == m_nMaxFrame - 1)		
			{
                if( !m_bRepeatForever)
				{
                    m_nPlayCount++;
                    if(m_nPlayCount == m_nRepeatCount)
                    {
                        this->_callEventDelegator( TypeDefineNS::kTag_EventCall_LastFrame );
                    }
                    
				}
			}
            
			else if ( m_nCurrentFrame == m_nMaxFrame )
			{
				if( m_bRepeatForever )
				{
					playAnimation( 0, true );
				}
				else
				{
                    //added by JU.JEON 2013.07.01
                    
                    if(m_nPlayCount == m_nRepeatCount)  
                    {
                        //stopAnimation( false );
                        //modified JU.JEON
                        m_nRepeatCount = 1;
                        m_nPlayCount = 0;
                        m_eState = TypeDefineNS::kState_Stop;
                        
                    }else{
                        playAnimation(0);
                    }
				}
			}
		}

		//
		// ∏µÁ Ω∫«¡∂Û¿Ã∆Æ æ˜µ•¿Ã∆Æ
		for( unsigned int i = 0; i < m_stl_Sprites_vt.size(); i++ )
			m_stl_Sprites_vt[i]->updateFrame( m_stl_KeyFrameData_vt[i], m_nCurrentFrame, dt );

		if( m_eState == TypeDefineNS::kState_Play )
			m_nCurrentFrame++;		// 1«¡∑π¿” ¡ı∞°

		this->_callEventDelegator( TypeDefineNS::kTag_EventCall_Update );
	}

//    bool CJAnimation::updateOneFrame( void )
//	{
//		m_bOneFrameCheck = false;
//        
//		if( this->isNone() )
//		{
//			this->schedule( schedule_selector( CJAnimation::_updateOneFrameAnimation ), 1.0f / 60.0f );
//			return true;
//		}
//        
//		return false;
//	}
//    
//	void CJAnimation::_updateOneFrameAnimation( float dt )
//	{
//		if( m_bOneFrameCheck )
//		{
//			this->unschedule( schedule_selector( CJAnimation::_updateOneFrameAnimation ) );
//			m_bOneFrameCheck = false;
//		}
//
//		//
//		// ∏µÁ Ω∫«¡∂Û¿Ã∆Æ æ˜µ•¿Ã∆Æ
//		for( unsigned int i = 0; i < m_stl_Sprites_vt.size(); i++ )
//			m_stl_Sprites_vt[i]->updateFrame( m_stl_KeyFrameData_vt[i], m_nCurrentFrame, dt );
//
//		m_bOneFrameCheck = true;
//	}
//    
//	void CJAnimation::_update( float dt )
//	{
//        
//	}
    
	void CJAnimation::_updateCurrentFrame(void)
	{
		for( unsigned int i = 0; i < m_stl_Sprites_vt.size(); i++ )
			m_stl_Sprites_vt[i]->updateFrame( m_stl_KeyFrameData_vt[i], m_nCurrentFrame );
	}

    void CJAnimation::runActionWithAllSprite(cocos2d::CCAction* t_pAction)
    {
        for( unsigned int i = 0; i < m_stl_Sprites_vt.size(); i++ )
        {
            CCObject* pCpy = t_pAction->copy();
            
            m_stl_Sprites_vt[i]->runAction( (CCAction*)pCpy );
        }
        
        //t_pAction->release();
    }
    
    
    CJAnimationSprite* CJAnimation::getSpriteFromSpriteName( std::string strName )
    {
        STL_VECTOR_ITER_Sprite iter = m_stl_Sprites_vt.begin();
        CJAnimationSprite* pSprite = NULL;
        
        while( iter != m_stl_Sprites_vt.end() )
        {
            pSprite = *iter;
            CCLog("strName %s", strName.c_str());
            CCLog("getsprite %s", pSprite->getSpriteName().c_str());
            if( strName.compare( pSprite->getSpriteName() ) == 0 )
            {
                return pSprite;
            }
            
            iter++;
        }
        
        return NULL;
    }
    
    
	void CJAnimation::drawBoundingBox( void )
	{
		CCPoint pos = CCNode::getPosition();
//		float scaleX = CCNode::getScaleX();
//		float scaleY = CCNode::getScaleY();
		for( unsigned int i = 0; i < m_stl_Sprites_vt.size(); i++ )
		{
			CCRect bd = m_stl_Sprites_vt[i]->getBoundingBox( pos );

			ccDrawLine( bd.origin, ccp( bd.origin.x + bd.size.width, bd.origin.y ) );																// æ∆∑°
			ccDrawLine( ccp( bd.origin.x + bd.size.width, bd.origin.y ), ccp( bd.origin.x + bd.size.width, bd.origin.y + bd.size.height ) );		// ø¿∏•¬ 
			ccDrawLine( ccp( bd.origin.x + bd.size.width, bd.origin.y + bd.size.height ), ccp( bd.origin.x, bd.origin.y + bd.size.height ) );		// ¿ß
			ccDrawLine( ccp( bd.origin.x, bd.origin.y + bd.size.height ), bd.origin );																// øﬁ¬ 		
		}
	}
    
    
    
    CCSize CJAnimation::getSizeOfAnimation()
    {
        STL_VECTOR_ITER_Sprite iter = m_stl_Sprites_vt.begin();
        
        float minX;
        float maxX;
        float minY;
        float maxY;
        
        bool isFirst = false;
        while( iter != m_stl_Sprites_vt.end() )
        {
            if ((*iter)->isVisible() == true)
            {
                CCRect spSize = (*iter)->boundingBox();
                
                float posX = (*iter)->boundingBox().origin.x;
                float posY = (*iter)->boundingBox().origin.y;
                
//                CCLog("%s width:%f height:%f",(*iter)->getSpriteName().c_str(), spSize.size.width, spSize.size.height);
//                CCLog("posX:%f posY:%f", posX, posY);
                
                if (isFirst == false)
                {
                    minX = posX;
                    maxX = minX + spSize.size.width;
                    minY = posY;
                    maxY = minY + spSize.size.height;
                    
                    isFirst = true;
                }
                
                if (posX < minX)
                {
                    minX = posX;
                }
                
                if (posY < minY)
                {
                    minY = posY;
                }
                
                if(posX + spSize.size.width > maxX)
                {
                    maxX = posX + spSize.size.width;
                }
                
                if(posY + spSize.size.height > maxY)
                {
                    maxY = posY + spSize.size.height;
                }
            }
            iter++;
        }
        
        CCSize result = CCSizeMake(maxX - minX, maxY - minY);
        return result;
    }
    
    CCPoint CJAnimation::getPositionOfAnimation()
    {
        CCPoint position = CCPointMake(0, 0);
        
        STL_VECTOR_ITER_Sprite iter = m_stl_Sprites_vt.begin();
        
        bool isFirst = false;
        while( iter != m_stl_Sprites_vt.end() )
        {
            if ((*iter)->isVisible() == true)
            {
                float posX = (*iter)->boundingBox().origin.x;
                float posY = (*iter)->boundingBox().origin.y;
                
                if (isFirst == false)
                {
                    position.x = posX;
                    position.y = posY;
                    isFirst = true;
                }
                
                if (position.x > posX)
                {
                    position.x = posX;
                }
                
                if (position.y > posY)
                {
                    position.y = posY;
                }
            }

            iter++;
        }
        return position;
    }

    
	
}	// end of namespace CJFlashNS