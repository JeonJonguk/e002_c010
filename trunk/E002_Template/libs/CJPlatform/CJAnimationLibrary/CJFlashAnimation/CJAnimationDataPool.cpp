// #include "HXmlPreHeader.h"
// 
// #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
// #include "CJFlash_util.h"
// #else
// #include "../CJFlash_util.h"
// #endif


#include "CJAnimationDataPool.h"

#include "CJAnimationSprite.h"
#include "CJAnimation.h"


using namespace cocos2d;
using namespace CJFlash;


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////



namespace CJFlash
{

	CJAnimationDataPool::CJAnimationDataPool(void)
	{
        pStl_vt_CJAni = new std::vector<CJAnimation*>;
	}

	CJAnimationDataPool::~CJAnimationDataPool(void)
	{
		STL_MULTIMAP_ANIMATIONSHEETS::iterator AniSheetIter = m_stl_mmap_AnimationSheet.begin();
		while( AniSheetIter != m_stl_mmap_AnimationSheet.end() )
		{
			CJ_SAFE_DELETE( AniSheetIter->second );

			AniSheetIter++;
		}
		m_stl_mmap_AnimationSheet.clear();

		STL_MULTIMAP_SPRITESHEETS::iterator SprSheetiter = m_stl_mmap_SpriteSheet.begin();
		while( SprSheetiter != m_stl_mmap_SpriteSheet.end() )
		{
			CJ_SAFE_DELETE( SprSheetiter->second );

			SprSheetiter++;
		}
		m_stl_mmap_SpriteSheet.clear();

		STL_MULTIMAP_KEYFRAMEANIDATAS::iterator KeyFrameSheetiter = m_stl_mmap_KeyFrameSheet.begin();
		while( KeyFrameSheetiter != m_stl_mmap_KeyFrameSheet.end() )
		{
			CJ_SAFE_DELETE( KeyFrameSheetiter->second );

			KeyFrameSheetiter++;
		}
		m_stl_mmap_KeyFrameSheet.clear();
        

        
        STL_MULTIMAP_ANIMATIONS::iterator Animationiter = m_stl_mmap_Animations.begin();
		while( Animationiter != m_stl_mmap_Animations.end() )
		{
			CJ_SAFE_DELETE( Animationiter->second );
            
			Animationiter++;
		}
		m_stl_mmap_Animations.clear();

        pStl_vt_CJAni->clear();
        CC_SAFE_DELETE(pStl_vt_CJAni);
	}

	bool CJAnimationDataPool::setup(void)
	{

		return true;
	}

	bool CJAnimationDataPool::_addAnimationSheetData( CJFlash::SAnimationSheet* pSheet )
	{
		//
		// map 교체 작업
		std::pair<std::string, CJFlash::SAnimationSheet*> Enumerator( pSheet->strAniName, pSheet );

		m_stl_mmap_AnimationSheet.insert( Enumerator );

		return true;
	}

	bool CJAnimationDataPool::_addSpriteSheetData( SSpriteSheet* pSheet )
	{
		//
		// map 교체 작업 
		std::pair<std::string, CJFlash::SSpriteSheet*> Enumerator( pSheet->name, pSheet );

		m_stl_mmap_SpriteSheet.insert( Enumerator );

		return true;
	}

	bool CJAnimationDataPool::_addKeyFrameAniData( SKeyFrameAniData* pKeyFrameAniData )
	{
		//
		// map 교체 작업
		std::pair<std::string, CJFlash::SKeyFrameAniData*> Enumerator( pKeyFrameAniData->strAnimationName, pKeyFrameAniData);

		m_stl_mmap_KeyFrameSheet.insert( Enumerator );

		return true;
	}

	//************************************
	// Method:    getAnimationSheetFromAnimationName
	// FullName:  CJAnimationDataPool::getAnimationSheetFromAnimationName
	// Access:    public 
	// Returns:   const myTypes::gsMyAnimationSheet*
	// Qualifier: 애니메이션 이름으로 해당하는 애니메이션 시트 데이터를 가져온다
	// Parameter: std::string aniName - 찾을 애니메이션 이름
	//************************************
	const CJFlash::SAnimationSheet* CJAnimationDataPool::getAnimationSheetFromAnimationName( std::string aniName )
	{
		STL_MULTIMAP_ANIMATIONSHEETS::iterator iter = m_stl_mmap_AnimationSheet.find( aniName );

		return iter != m_stl_mmap_AnimationSheet.end() ? iter->second : NULL;
	}


	//************************************
	// Method:    getSpriteSheetFromSpriteName
	// FullName:  CJAnimationDataPool::getSpriteSheetFromSpriteName
	// Access:    public 
	// Returns:   const gsMySpriteSheet*
	// Qualifier: 스프라이트 이름으로부터 해당 스프라이트의 시트 정보를 가져온다
	// Parameter: std::string spriteName - 찾을 스프라이트 이름
	//************************************
	const SSpriteSheet* CJAnimationDataPool::getSpriteSheetFromSpriteName( std::string spriteName )
	{
		STL_MULTIMAP_SPRITESHEETS::iterator iter = m_stl_mmap_SpriteSheet.find( spriteName );

		return iter != m_stl_mmap_SpriteSheet.end() ? iter->second : NULL;
	}
 

	//************************************
	// Method:    allocSpriteFromSpriteName
	// FullName:  CJAnimationDataPool::allocSpriteFromSpriteName
	// Access:    public 
	// Returns:   CXmlSprite*
	// Qualifier: 스프라이트 이름으로 해당 스프라이트 시트 정보를 토대로 
	//			  스프라이트 객체를 생성한다.
	// Parameter: std::string spriteName - 생성할 스프라이트 이름
	//************************************
	CJAnimationSprite* CJAnimationDataPool::createSpriteObjectFromSpriteName( std::string spriteName )
	{
		const SSpriteSheet* pSheet = getSpriteSheetFromSpriteName( spriteName );
//        const SKeyFrameAniData* pAniData = getSpriteFrameAniDataFromSpriteName( spriteName );
        
		if( pSheet == NULL )
		{
			CCMessageBox( spriteName.c_str(), NOT_SPR_SHEET );
			return NULL;
		}

		CJAnimationSprite* pDesSprite = new CJAnimationSprite;
		if( pDesSprite == NULL )
			return NULL;

		pDesSprite->_setSheet( pSheet );
//        pDesSprite->_setAniData(pAniData);

		return pDesSprite;
	}

	//************************************
	// Method:    allocAnimationFromAnimationName
	// FullName:  CJAnimationDataPool::allocAnimationFromAnimationName
	// Access:    public 
	// Returns:   CJAnimation*
	// Qualifier: 애니메이션 이름으로 해당 애니메이션의 객체를 생성한다.
	// Parameter: std::string aniName - 생성할 애니메이션 이름
	//************************************
	CJAnimation* CJAnimationDataPool::createAnimationObjectFromAnimationName( std::string aniName )
	{
		//
		// 저장된 애니메이션 시트에서 검색한다.
		const SAnimationSheet* pAniSheet = getAnimationSheetFromAnimationName( aniName );
		if( pAniSheet == NULL )
		{
			CCMessageBox( aniName.c_str(), NOT_ANI_SHEET );
			return NULL;
		}

        
        std::vector<CJAnimation*>::iterator aniIter = pStl_vt_CJAni->begin();
        
        for (; aniIter != pStl_vt_CJAni->end(); ++aniIter)
        {
            CJAnimation* ani = *aniIter;
            if(ani->getName() == aniName)
            {
                pStl_vt_CJAni->erase(aniIter);
                break;
            }
        }
        
        STL_MULTIMAP_ANIMATIONS::iterator it = m_stl_mmap_Animations.begin();
        
        for(; it != m_stl_mmap_Animations.end(); it++)
        {
            
            if(it->first == aniName)
            {
                CC_SAFE_RELEASE(it->second);
                m_stl_mmap_Animations.erase(it);
                break;
            }
        }
        

        

		//
		// 애니메이션 객체 생성
		CJAnimation* pAnimation = new CJAnimation;
		CC_ASSERT( pAnimation != NULL );

        pAnimation->m_bIsCommonPath = _mIsCommon;
        
		pAnimation->_setAnimationName( aniName );
		pAnimation->_setMaxFrame( pAniSheet->nFrameCount );
        pAnimation->_setDataPool(this);

		//
		//

		STL_MULTIMAP_KEYFRAMEANIDATAS::iterator iter = m_stl_mmap_KeyFrameSheet.find( aniName );	// 애니메이션을 찾음
		if( iter == m_stl_mmap_KeyFrameSheet.end() )
		{
			return pAnimation;
		}

		SKeyFrameAniData* pKeyFrameData = iter->second;
		CJAnimationSprite* pCJAnimationSprite = NULL;


		//
		// 해당 애니메이션에 속한 모든 스프라이트들을 찾아서 애니메이션 객체를 구성함
		while( iter->first == pKeyFrameData->strAnimationName )
		{
			pKeyFrameData = iter->second;

			pCJAnimationSprite = createSpriteObjectFromSpriteName( pKeyFrameData->strSpriteName );
            
            //added Jonguk.JEON
            pCJAnimationSprite->_setAniData(pKeyFrameData);
            
			pAnimation->_addKeyFrameAniData( pKeyFrameData );
			pAnimation->_addSpriteData( pCJAnimationSprite );

			iter++;

			if( iter == m_stl_mmap_KeyFrameSheet.end() )
				break;
		}
        
        std::pair<std::string, CJFlash::CJAnimation*> Enumerator( pAniSheet->strAniName, pAnimation );
        m_stl_mmap_Animations.insert( Enumerator );


        
        aniIter = pStl_vt_CJAni->begin();
        
        bool isOverlap = false;
        for (; aniIter != pStl_vt_CJAni->end(); ++aniIter)
        {
            CJAnimation* ani = *aniIter;
            if(ani == pAnimation)
            {
                isOverlap = true;
            }
        }
        
        if (isOverlap == false)
        {
            pStl_vt_CJAni->push_back(pAnimation);
        }
        
        pAnimation->preload();
		return pAnimation;
	}
    void CJAnimationDataPool::createAllAnimations()
    {
        if( m_stl_mmap_AnimationSheet.size() <= 0 )
			return;
        
		STL_MULTIMAP_ANIMATIONSHEETS::iterator iter = m_stl_mmap_AnimationSheet.begin();
		SAnimationSheet* pAniSheet = NULL;
        
		CJAnimation* pAni = NULL;
        
        pStl_vt_CJAni->clear();
        
		while( iter != m_stl_mmap_AnimationSheet.end() )
		{
			pAniSheet = iter->second;
            
			pAni = createAnimationObjectFromAnimationName( pAniSheet->strAniName );
            
			iter++;
		}
    }

	std::vector<CJAnimation*>* CJAnimationDataPool::getAllAnimations()
	{
		return pStl_vt_CJAni;
	}
    
    std::vector<CJAnimation*>* CJAnimationDataPool::getAllAnimationsAndCreate()
	{
        createAllAnimations();
        
		return pStl_vt_CJAni;
	}
    
    CJAnimation* CJAnimationDataPool::getAnimationFromAnimationName(std::string aniName)
    {
        STL_MULTIMAP_ANIMATIONS::iterator it = m_stl_mmap_Animations.find(aniName);
        
        CCAssert(it != m_stl_mmap_Animations.end(), "animation name is not found");
        
        return (CJAnimation*)it->second;
    }
    
    CJAnimation* CJAnimationDataPool::getAnimationFromAnimationKey(std::string aniKey)
    {
        STL_MULTIMAP_ANIMATIONS::iterator it = m_stl_mmap_Animations.begin();
        
        CJAnimation* _flashAni = NULL;
        for(; it != m_stl_mmap_Animations.end(); it++)
        {
            CJAnimation* ani = it->second;
            if(ani->getKey() == aniKey)
            {
                _flashAni = ani;
                break;
            }
        }
        
        CCAssert(_flashAni != NULL, "animation key is not found");
        return _flashAni;
    }
    
    
    int CJAnimationDataPool::getAnimationCount()
    {
        return m_stl_mmap_Animations.size();
    }

}	// end of namespace CJFlashNS