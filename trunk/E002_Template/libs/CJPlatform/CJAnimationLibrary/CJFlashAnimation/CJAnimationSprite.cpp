#include "CJHAnimationPreHeader.h"
#include "CJFlashResourcePathDirector.h"
#include "CJFlashDevice.h"

#include "CJAnimationSprite.h"



using namespace cocos2d;
using namespace CJFlash;

namespace CJFlash
{

	CJAnimationSprite::CJAnimationSprite( void )
	{
		m_pSheetInfo = NULL;

		m_IsLoad = false;
        
        //added Jonguk.JEON at 2013.05.29
        m_pKeyFrameAniData = NULL;
        
        _myFilePath= "";
        
        deltaPos = CCPointZero;
	}

	CJAnimationSprite::~CJAnimationSprite( void )
	{
        
        this->unload();
        
		m_pSheetInfo = NULL;
        
        //added Jonguk.JEON at 2013.05.29
        m_pKeyFrameAniData = NULL;
        
        _myFilePath = "";
		
	}
    
    void CJAnimationSprite::addChild(CCNode *child, int zOrder, int tag)
    {
        if (child->getParent() != NULL) {
            child->removeFromParent();
        }
        CCSprite::addChild(child, zOrder, tag);
    }
    void CJAnimationSprite::addChild(CCNode *child, int zOrder)
    {
        CCSprite::addChild(child, zOrder);
    }
    
    void CJAnimationSprite::addChild(CCNode *child)
    {
        CCSprite::addChild(child);
    }
    


	bool CJAnimationSprite::preload( bool bIsCommonPath )
	{
		bool bRet = true;
 
        deltaPos = CCPointZero;
        
		if( !m_IsLoad )
		{
            std::string filePath;
            if (bIsCommonPath == false)
            {
                filePath = CResourcePathDirector::sharedInstance()->getRealPath( m_pSheetInfo->filePath );
            }
            else if (bIsCommonPath == true)
            {
                filePath = CResourcePathDirector::sharedInstance()->getCommonPath( m_pSheetInfo->filePath );
            }
            
            _myFilePath = filePath;
            
			CCTextureCache::sharedTextureCache()->addImage( filePath.c_str() );
			this->initWithTexture( CCTextureCache::sharedTextureCache()->textureForKey( filePath.c_str() ) );
		}

		this->setAnchorPoint( m_pSheetInfo->registrationPoint );
		//this->setPosition( ccp( -500.0f, -500.0f ) );
        
        
		m_IsLoad = true;

		return bRet;
	}

	void CJAnimationSprite::unload( void )
	{
		//this->cleanup();

		if( m_IsLoad )
		{
			CCTextureCache::sharedTextureCache()->removeTextureForKey( _myFilePath.c_str() );
		}

		m_IsLoad = false;
	}
    
    void CJAnimationSprite::setMoveToPosition(CCPoint pt)
    {
        deltaPos = pt;
    }

	void CJAnimationSprite::updateFrame( SKeyFrameAniData* pKeyFrameAniData, unsigned int frame, float dt )
	{
		if( frame >= pKeyFrameAniData->nMaxFrame )
			return ;

		const SKeyFrameData* pData = pKeyFrameAniData->stl_KeyFrame_vt[frame];

		if( pData == NULL )
			return ;
        
        if((GLubyte)(pData->fKeyFrameAlpha) < 3)
        {
            this->setVisible(false);
        }
        else
        {
//            this->setPosition( pData->KeyFramePosition );
            this->setPosition( ccp(pData->KeyFramePosition.x + deltaPos.x, pData->KeyFramePosition.y + deltaPos.y) );
            this->setScaleX( pData->KeyFrameScale.x );
            this->setScaleY( pData->KeyFrameScale.y );
            this->setRotation( pData->fKeyFrameRotation );
            this->setOpacity( (GLubyte)(pData->fKeyFrameAlpha) );
            this->setVisible(true);

        }
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CCRect spSize = this->boundingBox();
        
        float posX = this->boundingBox().origin.x;
        float posY = this->boundingBox().origin.y;
        
        float minX = posX;
        float maxX = minX + spSize.size.width;
        float minY = posY;
        float maxY = minY + spSize.size.height;
        
//        if (minX > winSize.width || maxX < 0 || minY > winSize.height || maxY < 0 )
//        {
//            this->setVisible(false);
//        }
	}

	void CJAnimationSprite::updateFrame( SKeyFrameAniData* pKeyFrameAniData, unsigned int frame )
	{
		if( frame >= pKeyFrameAniData->nMaxFrame )
			return ;

		const SKeyFrameData* pData = pKeyFrameAniData->stl_KeyFrame_vt[frame];

		if( pData == NULL )
			return ;

        if((GLubyte)(pData->fKeyFrameAlpha) < 3)
        {
            this->setVisible(false);
        }
        else
        {
            //		this->setPosition( pData->KeyFramePosition );
            this->setPosition( ccp(pData->KeyFramePosition.x + deltaPos.x, pData->KeyFramePosition.y + deltaPos.y) );
            this->setScaleX( pData->KeyFrameScale.x );
            this->setScaleY( pData->KeyFrameScale.y );
            this->setRotation( pData->fKeyFrameRotation );
            this->setOpacity( (GLubyte)(pData->fKeyFrameAlpha) );
            this->setVisible(true);
        }
        
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CCRect spSize = this->boundingBox();
        
        float posX = this->boundingBox().origin.x;
        float posY = this->boundingBox().origin.y;
        
        float minX = posX;
        float maxX = minX + spSize.size.width;
        float minY = posY;
        float maxY = minY + spSize.size.height;

        
//        if (minX > winSize.width || maxX < 0 || minY > winSize.height || maxY < 0 )
//        {
//            this->setVisible(false);
//        }
	}

	const cocos2d::CCRect CJAnimationSprite::getBoundingBox( cocos2d::CCPoint& pos )
	{
		CCRect bd = this->boundingBox();

		CDeviceResolution::sharedInstance()->convertResolutionVariable( &bd );
		bd.origin.x += pos.x;
		bd.origin.y += pos.y;

		return bd;
	}


    /**
     * @author  Jonguk JEON
     * @brief	get CJAnimationSprite all position vector.
     * @date    2013.05.29
     */
    std::vector<CCPoint>* CJAnimationSprite::getVectorSpritePositions()
    {
        m_vecPositions = new std::vector<CCPoint>();
        
        for (int i = 0; i<m_pKeyFrameAniData->nMaxFrame; i++) {
            SKeyFrameData* pData = m_pKeyFrameAniData->stl_KeyFrame_vt[i];
            CCPoint ptPosition = pData->KeyFramePosition;
            
            //temp exclusion ccpointzero.
            if (ptPosition.x != 0 || ptPosition.y != 0) {
                m_vecPositions->push_back(ptPosition);
            }else{
                //CCLog("point = zero");
            }
        }
        return m_vecPositions;
        
    }
    
    // 	void CJAnimationSprite::drawBoundingBox( cocos2d::CCPoint& ptPos, float fScaleX, float fScaleY )
    // 	{
    // 		glEnable( GL_LINE_SMOOTH );
    // 		glColor4ub( 0, 255, 0, 255 );
    //
    // 		CCRect bd = getBoundingBox( ptPos );
    //
    // 		ccDrawLine( bd.origin, ccp( bd.origin.x + bd.size.width, bd.origin.y ) );																// 아래
    // 		ccDrawLine( ccp( bd.origin.x + bd.size.width, bd.origin.y ), ccp( bd.origin.x + bd.size.width, bd.origin.y + bd.size.height ) );		// 오른쪽
    // 		ccDrawLine( ccp( bd.origin.x + bd.size.width, bd.origin.y + bd.size.height ), ccp( bd.origin.x, bd.origin.y + bd.size.height ) );		// 위
    // 		ccDrawLine( ccp( bd.origin.x, bd.origin.y + bd.size.height ), bd.origin );																// 왼쪽
    // 	}
}	// end of namespace CJFlash
