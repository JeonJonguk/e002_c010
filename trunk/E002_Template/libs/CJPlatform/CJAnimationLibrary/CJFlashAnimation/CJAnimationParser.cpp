#include "cocos2d.h"

#include "CJAnimationParser.h"
#include "CJFlashResourcePathDirector.h"
#include "CJAnimationDataPool.h"


#include <time.h>
#include <fstream>

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#define		MARGIN		-24.0f

#else

#define		MARGIN		0.0f

#endif



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define XML_ENCODING_TYPE		"UTF-8"


using namespace cocos2d;
using namespace CJFlash;

namespace CJFlash
{
    rapidjson::Document initParse(const char *pageName)
    {
        
        rapidjson::Document document;
        
        std::string filename = CCFileUtils::sharedFileUtils()->fullPathForFilename(pageName);
        CCLog(" initParse filename %s", filename.c_str());
        
        unsigned long buffsize = 0;
        unsigned char* pData = NULL;
        
        char* pszRet = 0;
        pData = CCFileUtils::sharedFileUtils()->getFileData(filename.c_str(), "rb", &buffsize);
        do
        {
            CC_BREAK_IF(!pData || buffsize <= 0);
            pszRet = new char[buffsize+1];
            pszRet[buffsize] = '\0';
            memcpy(pszRet, pData, buffsize);
            CC_SAFE_DELETE_ARRAY(pData);
        } while (false);
        
        
        if (document.Parse<0>(pszRet).HasParseError())
        {
            CCLog("document ParseError");
        }
        else
        {
            CCLog("document ParseSuccess");
        }
        
        // add Memory leak by Lee.YJ at 2013.03.07
        CC_SAFE_DELETE(pszRet);
        
        
        return document;
    }

	CJAnimationDataPool* parseJsonAnimation(const char* szSheetFileName, const char* szAnimationsFileName, bool appendFullPath )
	{
		CJAnimationDataPool* pAniManager = new CJAnimationDataPool;
        
		if( pAniManager == NULL )
			return NULL;
        
		// Sheets 파일 파싱
        
		_CJSheetDelegator sheetDelegator;
		sheetDelegator.setAnimationManager( pAniManager );
        
        std::string filePath;
        if (appendFullPath == true) {
            //fix
            pAniManager->_mIsCommon = false;
            filePath = CJ_ROOT_PATH( szSheetFileName );
        }else{
            pAniManager->_mIsCommon = true;
            filePath = szSheetFileName;
        }
        
        sheetDelegator.setElement(CJFlash::initParse(filePath.c_str()));
        
        
		//
		// Animations 파일 파싱
		_CJAnimationsDelegator animationDelegator;
		animationDelegator.setAnimationManager( pAniManager );
        
        
        //added by JU.JEON 2013.07.14
        //for common path
        if (appendFullPath == true) {
            //fix
            pAniManager->_mIsCommon = false;
            filePath = CJ_ROOT_PATH( szAnimationsFileName );
        }else{
            pAniManager->_mIsCommon = true;
            filePath = szAnimationsFileName;
        }
        
        animationDelegator.setElement(CJFlash::initParse(filePath.c_str()));
        
		return pAniManager;
	}

    
    CJAnimationDataPool* parseXmlAnimation(const char* szSheetFileName, const char* szAnimationsFileName, bool appendFullPath )
	{
		CCSAXParser parser;
        
		CJAnimationDataPool* pAniManager = new CJAnimationDataPool;
        
		if( pAniManager == NULL )
			return NULL;
        
		// Sheets 파일 파싱
		_CJSheetDelegator sheetDelegator;
		sheetDelegator.setAnimationManager( pAniManager );
		parser.init( XML_ENCODING_TYPE );
		parser.setDelegator( &sheetDelegator );
        
        //const char* filePath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath( CJ_ROOT_PATH_C( szSheetFileName ) );
        //const char* filePath = CCFileUtils::fullPathFromRelativePath( CJ_ROOT_PATH( szSheetFileName ).c_str() );
        
        //added by JU.JEON 2013.07.14
        //for common path
        std::string filePath;
        if (appendFullPath == true) {
            //fix
            filePath = CJ_ROOT_PATH( szSheetFileName );
        }else{
            filePath = szSheetFileName;
        }
        
        
		if( parser.parse( filePath.c_str() ) == false )
		{
			return NULL;
		}
        
        
		//
		// Animations 파일 파싱
		_CJAnimationsDelegator animationDelegator;
		animationDelegator.setAnimationManager( pAniManager );
		parser.init( XML_ENCODING_TYPE );
		parser.setDelegator( &animationDelegator );
        
		//filePath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath( CJ_ROOT_PATH_C( szAnimationsFileName ) );
        //filePath = CCFileUtils::fullPathFromRelativePath( CJ_ROOT_PATH( szAnimationsFileName ).c_str() );
        
        //added by JU.JEON 2013.07.14
        //for common path
        if (appendFullPath == true) {
            //fix
            filePath = CJ_ROOT_PATH( szAnimationsFileName );
        }else{
            filePath = szAnimationsFileName;
        }
        
        
		if( parser.parse( filePath.c_str() ) == false )
		{
			return NULL;
		}
        
		return pAniManager;
	}

    

	bool IsStringEqual( const char* str1, const char* str2 ){ 
		return strcmp( str1, str2 ) == 0 ? true : false; 
	}


    
    ////

	////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////
    
    void _CJSheetDelegator::setElement(rapidjson::Document document)
    {
        
        if (document.HasMember("Textures"))
        {
            const rapidjson::Value& texture = document["Textures"];
            
            if (texture.HasMember("TextureSheet"))
            {
                const rapidjson::Value& textureSheet = texture["TextureSheet"];
                
                const rapidjson::Value& textures = textureSheet["Texture"];
                
                for (int textureIdx = 0; textureIdx < textures.Size(); textureIdx++)
                {
                    const rapidjson::Value& atts = textures[textureIdx]["@attributes"];
                    
                    SSpriteSheet* pSheet;
                    pSheet = new SSpriteSheet;
                    
                    if (atts.HasMember("name"))
                    {
                        pSheet->name.append(atts["name"].GetString());
                    }
                    
                    if(atts.HasMember("width"))
                    {
                        pSheet->nWidth = STRING_TO_FLOAT(atts["width"].GetString());
                    }
                    
                    if(atts.HasMember("height"))
                    {
                        pSheet->nHeight = STRING_TO_FLOAT(atts["height"].GetString());
                    }
                    
                    if(atts.HasMember("path"))
                    {
                        pSheet->filePath.append(atts["path"].GetString());
                    }
                    
                    if(atts.HasMember("registrationPointX"))
                    {
                        pSheet->registrationPoint.x = STRING_TO_FLOAT(atts["registrationPointX"].GetString());
                    }
                    
                    if(atts.HasMember("registrationPointY"))
                    {
                        pSheet->registrationPoint.y = STRING_TO_FLOAT(atts["registrationPointY"].GetString());
                    }
                    
                    if(atts.HasMember("zIndex"))
                    {
                        pSheet->zIndex = STRING_TO_INT(atts["zIndex"].GetString());
                    }
                    
                    pSheet->registrationPoint.x = pSheet->registrationPoint.x / pSheet->nWidth;
                    pSheet->registrationPoint.y = 1.0f - (pSheet->registrationPoint.y / pSheet->nHeight);
                    
                    m_pAniManager->_addSpriteSheetData( pSheet );
                }
            }
        }
    }


	void _CJSheetDelegator::startElement( void *ctx, const char *name, const char **atts )
	{
		if( IsStringEqual( name, "Texture" ) )
		{
			SSpriteSheet* pSheet;
			pSheet = new SSpriteSheet;
            
			while( *atts != NULL )
			{
				if( IsStringEqual( *atts, "name" ) )
				{
					atts++;
                    
					pSheet->name.append( *atts, strlen( *atts ) );
				}
				else if( IsStringEqual( *atts, "width" ) )
				{
					atts++;
                    
					pSheet->nWidth = STRING_TO_INT( *atts );
				}
				else if( IsStringEqual( *atts, "height" ) )
				{
					atts++;
                    
					pSheet->nHeight = STRING_TO_INT( *atts );
				}
				else if( IsStringEqual( *atts, "path" ) )
				{
					atts++;
                    
					pSheet->filePath.append( *atts, strlen( *atts ) );
                    
					// #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
					// 				pSheet->filePath = pSheet->filePath.substr( pSheet->filePath.find( '/' ) + 1, pSheet->filePath.size() );
					// #endif
				}
				else if( IsStringEqual( *atts, "registrationPointX" ) )
				{
					atts++;
                    
					pSheet->registrationPoint.x = STRING_TO_FLOAT( *atts );
				}
				else if( IsStringEqual( *atts, "registrationPointY" ) )
				{
					atts++;
                    
					pSheet->registrationPoint.y = STRING_TO_FLOAT( *atts );
				}
				else if( IsStringEqual( *atts, "zIndex" ) )
				{
					atts++;
                    
					pSheet->zIndex = STRING_TO_INT( *atts );
				}
                
				atts++;
			}
            
			//
			// 변환작업
			pSheet->registrationPoint.x = pSheet->registrationPoint.x / pSheet->nWidth;
			pSheet->registrationPoint.y = 1.0f - (pSheet->registrationPoint.y / pSheet->nHeight);
            
			m_pAniManager->_addSpriteSheetData( pSheet );
		}
	}

	////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////
    
    void _CJAnimationsDelegator::setElement(rapidjson::Document document)
    {
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        if (document.HasMember("Animations"))
        {
            const rapidjson::Value& animations = document["Animations"];
            
            if (animations.HasMember("Animation"))
            {
                const rapidjson::Value& animation = animations["Animation"];
                
                for (int animationIdx = 0; animationIdx < animation.Size(); animationIdx++)
                {
                    m_pAnimationSheet = new SAnimationSheet;
                    
                    const rapidjson::Value& atts = animation[animationIdx]["@attributes"];

                    
                    if (atts.HasMember("frameCount"))
                    {
                        m_pAnimationSheet->nFrameCount = STRING_TO_INT(atts["frameCount"].GetString());
                    }
                    
                    if (atts.HasMember("name"))
                    {
                        m_pAnimationSheet->strAniName.append(atts["name"].GetString());
                    }

                    
                    const rapidjson::Value& parts = animation[animationIdx]["Part"];
                    
                    for (int partIdx = 0; partIdx < parts.Size(); partIdx++)
                    {
                        
                        m_pKeyFrameData = new SKeyFrameAniData;
                        
                        SKeyFrameData* m_pLastKeyFrameData;
                        
                        const rapidjson::Value& atts = parts[partIdx]["@attributes"];
                        
                        if (atts.HasMember("name"))
                        {
                            m_pKeyFrameData->strSpriteName = std::string(atts["name"].GetString());
                        }
                        
                        if(parts[partIdx].HasMember("Frame"))
                        {
                            const rapidjson::Value& frames = parts[partIdx]["Frame"];
                            
                            
                            for (int frameIdx = 0; frameIdx < frames.Size(); frameIdx++)
                            {
                                const rapidjson::Value& atts = frames[frameIdx]["@attributes"];
                                
                                
                                SKeyFrameData* KeyFrameData = NULL;
                                KeyFrameData = new SKeyFrameData;
                                
                                if(atts.HasMember("index"))
                                {
                                    KeyFrameData->nKeyFrameIndex = STRING_TO_INT(atts["index"].GetString());
                                }
                                
                                float tempX = -10000;
                                if(atts.HasMember("x"))
                                {
                                    KeyFrameData->KeyFramePosition.x = STRING_TO_FLOAT( atts["x"].GetString() );
                                    
                                    tempX = KeyFrameData->KeyFramePosition.x;
                                }
                                
                                if(atts.HasMember("y"))
                                {
                                    KeyFrameData->KeyFramePosition.y = STRING_TO_FLOAT( atts["y"].GetString() );
                                }
                                
                                if(atts.HasMember("scaleX"))
                                {
                                    KeyFrameData->KeyFrameScale.x = STRING_TO_FLOAT( atts["scaleX"].GetString() );
                                }
                                
                                if(atts.HasMember("scaleY"))
                                {
                                    KeyFrameData->KeyFrameScale.y = STRING_TO_FLOAT( atts["scaleY"].GetString() );
                                }
                                
                                if(atts.HasMember("rotation"))
                                {
                                    KeyFrameData->fKeyFrameRotation = STRING_TO_FLOAT( atts["rotation"].GetString() );
                                }
                                
                                if(atts.HasMember("alpha"))
                                {
                                    KeyFrameData->fKeyFrameAlpha = STRING_TO_FLOAT( atts["alpha"].GetString() ) * 255.0f;
                                }
                                
                                // @ added by pdj1117, Jonguk.JEON
                                // ***  잔상남는부분 수정.
                                if( m_nFrameCnt != KeyFrameData->nKeyFrameIndex )
                                {
                                    for( ; m_nFrameCnt < KeyFrameData->nKeyFrameIndex; m_nFrameCnt++ )
                                    {
                                        SKeyFrameData* LerpKeyFrameData = NULL;
                                        LerpKeyFrameData = new SKeyFrameData;
                                        
                                        LerpKeyFrameData->KeyFramePosition = m_pLastKeyFrameData->KeyFramePosition;
                                        LerpKeyFrameData->KeyFrameScale = m_pLastKeyFrameData->KeyFrameScale;
                                        LerpKeyFrameData->fKeyFrameRotation = m_pLastKeyFrameData->fKeyFrameRotation;
                                        LerpKeyFrameData->fKeyFrameAlpha = m_pLastKeyFrameData->fKeyFrameAlpha;
                                        LerpKeyFrameData->nKeyFrameIndex = m_nFrameCnt;
                                        
                                        m_pKeyFrameData->stl_KeyFrame_vt.push_back( LerpKeyFrameData );
                                    }
                                }
                                

                                
                                //
                                // 변환작업
//                                KeyFrameData->KeyFramePosition = CCDirector::sharedDirector()->convertToGL( KeyFrameData->KeyFramePosition );
                                KeyFrameData->KeyFramePosition.y += 768*((768-winSize.height)/768);
                                
                                m_pKeyFrameData->strAnimationName = m_pAnimationSheet->strAniName ;
                                
                                m_pKeyFrameData->nMaxFrame = m_nFrameCnt;
                                m_pKeyFrameData->stl_KeyFrame_vt.push_back( KeyFrameData );
                                
                                m_pLastKeyFrameData = KeyFrameData;

                                
                                m_nFrameCnt++;
                            }
                        }
                        
                        if (m_nFrameCnt < m_pAnimationSheet->nFrameCount)
                        {
                            for( ; m_nFrameCnt < m_pAnimationSheet->nFrameCount; m_nFrameCnt++ )
                            {
                                SKeyFrameData* LerpKeyFrameData = NULL;
                                LerpKeyFrameData = new SKeyFrameData;
                                
                                //add dongjin
                                LerpKeyFrameData->KeyFramePosition = m_pLastKeyFrameData->KeyFramePosition;
                                LerpKeyFrameData->KeyFrameScale = m_pLastKeyFrameData->KeyFrameScale;
                                LerpKeyFrameData->fKeyFrameRotation = m_pLastKeyFrameData->fKeyFrameRotation;
                                
                                LerpKeyFrameData->fKeyFrameAlpha  = m_pLastKeyFrameData->fKeyFrameAlpha;
                                LerpKeyFrameData->nKeyFrameIndex = m_nFrameCnt;
                                
                                m_pKeyFrameData->stl_KeyFrame_vt.push_back( LerpKeyFrameData );
                            }
                        }
                        
                        m_pKeyFrameData->nMaxFrame = m_nFrameCnt;
                        m_pAniManager->_addKeyFrameAniData( m_pKeyFrameData );
                        
                        m_nFrameCnt = 0;
                        
                    }
                    m_pAniManager->_addAnimationSheetData( m_pAnimationSheet );
                }
            }
        }
    }


	void _CJAnimationsDelegator::startElement( void *ctx, const char *name, const char **atts )
	{
		if( IsStringEqual( name, "Animation" ) )
		{
			m_pAnimationSheet = new SAnimationSheet;
            
			while( *atts != NULL )
			{
				if( IsStringEqual( *atts, "name" ) )
				{
					atts++;
                    
					m_pAnimationSheet->strAniName.append( *atts, strlen( *atts ) );
				}
				else if( IsStringEqual( *atts, "frameCount" ) )
				{
					atts++;
                    
					m_pAnimationSheet->nFrameCount = STRING_TO_INT( *atts );
				}
                
				atts++;
			}
		}
		else if( IsStringEqual( name, "Part" ) )
		{
			m_pKeyFrameData = new SKeyFrameAniData;
            
			while( *atts != NULL )
			{
				if( IsStringEqual( *atts, "name" ) )
				{
					atts++;
                    
					m_pKeyFrameData->strSpriteName = std::string( *atts );
				}
                
				atts++;
			}
		}
		else if( IsStringEqual( name, "Frame" ) )
		{
			SKeyFrameData* KeyFrameData = NULL;
			KeyFrameData = new SKeyFrameData;
            
			while( *atts != NULL )
			{
				if( IsStringEqual( *atts, "x" ) )
				{
					atts++;
                    
					KeyFrameData->KeyFramePosition.x = STRING_TO_FLOAT( *atts );
				}
				else if( IsStringEqual( *atts, "y" ) )
				{
					atts++;
                    
					KeyFrameData->KeyFramePosition.y = STRING_TO_FLOAT( *atts );
				}
				else if( IsStringEqual( *atts, "scaleX" ) )
				{
					atts++;
                    
					KeyFrameData->KeyFrameScale.x = STRING_TO_FLOAT( *atts );
				}
				else if( IsStringEqual( *atts, "scaleY" ) )
				{
					atts++;
                    
					KeyFrameData->KeyFrameScale.y = STRING_TO_FLOAT( *atts );
				}
				else if( IsStringEqual( *atts, "rotation" ) )
				{
					atts++;
                    
					KeyFrameData->fKeyFrameRotation = STRING_TO_FLOAT( *atts );
				}
				else if( IsStringEqual( *atts, "alpha" ) )
				{
					atts++;
                    
					KeyFrameData->fKeyFrameAlpha = STRING_TO_FLOAT( *atts ) * 255.0f;
				}
				else if( IsStringEqual( *atts, "index" ) )
				{
					atts++;
                    
					KeyFrameData->nKeyFrameIndex = STRING_TO_INT( *atts );
				}
                
				atts++;
			}
            
            //			// @ Very important code block...
            //			// CJFlash. YHM
            //			//
            //			// 프레임이 빠져있는곳을 메꿈 (알파값을 0을 줘서 안보이게 비어있는 프레임들을 설정함)
            //			if( m_nFrameCnt != KeyFrameData->nKeyFrameIndex )
            //			{
            //				for( ; m_nFrameCnt < KeyFrameData->nKeyFrameIndex; m_nFrameCnt++ )
            //				{
            //					SKeyFrameData* LerpKeyFrameData = NULL;
            //					LerpKeyFrameData = new SKeyFrameData;
            //
            //					LerpKeyFrameData->KeyFramePosition = KeyFrameData->KeyFramePosition;
            //					LerpKeyFrameData->KeyFrameScale = KeyFrameData->KeyFrameScale;
            //					LerpKeyFrameData->fKeyFrameRotation = KeyFrameData->fKeyFrameRotation;
            //					LerpKeyFrameData->fKeyFrameAlpha = 0.0f;
            //					LerpKeyFrameData->nKeyFrameIndex = m_nFrameCnt;
            //
            //					m_pKeyFrameData->stl_KeyFrame_vt.push_back( LerpKeyFrameData );
            //				}
            //			}
            //
            //			//
            //			// 변환작업
            //			KeyFrameData->KeyFramePosition.y += MARGIN;
            //			KeyFrameData->KeyFramePosition = CCDirector::sharedDirector()->convertToGL( KeyFrameData->KeyFramePosition );
            //
            //			m_pKeyFrameData->stl_KeyFrame_vt.push_back( KeyFrameData );
            //
            //			m_nFrameCnt++;
            
            
            
            // @ added by pdj1117, Jonguk.JEON
            // ***  잔상남는부분 수정.
            if( m_nFrameCnt != KeyFrameData->nKeyFrameIndex )
            {
                for( ; m_nFrameCnt < KeyFrameData->nKeyFrameIndex; m_nFrameCnt++ )
                {
                    SKeyFrameData* LerpKeyFrameData = NULL;
                    LerpKeyFrameData = new SKeyFrameData;
                    
                    LerpKeyFrameData->KeyFramePosition = KeyFrameData->KeyFramePosition;
                    LerpKeyFrameData->KeyFrameScale = KeyFrameData->KeyFrameScale;
                    LerpKeyFrameData->fKeyFrameRotation = KeyFrameData->fKeyFrameRotation;
                    LerpKeyFrameData->fKeyFrameAlpha = 0.0f;
                    LerpKeyFrameData->nKeyFrameIndex = m_nFrameCnt;
                    
                    m_pKeyFrameData->stl_KeyFrame_vt.push_back( LerpKeyFrameData );
                }
            }
            
            //
            // 변환작업
            KeyFrameData->KeyFramePosition = CCDirector::sharedDirector()->convertToGL( KeyFrameData->KeyFramePosition );
            KeyFrameData->KeyFramePosition.y += 768*((768-CCDirector::sharedDirector()->getWinSize().height)/768);
            
            m_pKeyFrameData->strAnimationName = m_pAnimationSheet->strAniName ;
            m_pKeyFrameData->nMaxFrame = m_nFrameCnt;
            m_pKeyFrameData->stl_KeyFrame_vt.push_back( KeyFrameData );
            
            m_nFrameCnt++;
        }
        
    }

	void _CJAnimationsDelegator::endElement( void *ctx, const char *name )
	{
        
        
        // @ added by pdj1117, Jonguk.JEON
        // ***  잔상남는부분 수정.
        if( IsStringEqual( name, "Animation" ) )
        {
            m_pAniManager->_addAnimationSheetData( m_pAnimationSheet );
        }
        else if( IsStringEqual( name, "Part" ) )
        {
            
            if (m_nFrameCnt < m_pAnimationSheet->nFrameCount) {
                for( ; m_nFrameCnt < m_pAnimationSheet->nFrameCount; m_nFrameCnt++ )
                {
                    SKeyFrameData* LerpKeyFrameData = NULL;
                    LerpKeyFrameData = new SKeyFrameData;
                    LerpKeyFrameData->fKeyFrameAlpha = 0.0f;
                    LerpKeyFrameData->nKeyFrameIndex = m_nFrameCnt;
                    
                    m_pKeyFrameData->stl_KeyFrame_vt.push_back( LerpKeyFrameData );
                }
            }
            
            m_pKeyFrameData->nMaxFrame = m_nFrameCnt;
            m_pAniManager->_addKeyFrameAniData( m_pKeyFrameData );
            
            m_nFrameCnt = 0;
        }
        
    }

}	// end of namespace CJFlash



