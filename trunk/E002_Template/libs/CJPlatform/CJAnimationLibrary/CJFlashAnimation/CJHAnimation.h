#ifndef __CJH_ANIMATION_H__
#define __CJH_ANIMATION_H__


#ifndef __COCOS2D_H__
#include "cocos2d.h"
#endif


#include "CJHAnimationPreHeader.h"

#include "CJAnimationParser.h"
#include "CJAnimationSprite.h"
#include "CJAnimation.h"
#include "CJAnimationDataPool.h"



// typedef std::vector<CJAnimation*>			STL_VECTOR_XmlAni;
// typedef std::vector<CJAnimation*>::iterator	STL_VECTOR_ITER_XmlAni;
// 
// typedef std::list<CJAnimation*>				STL_LIST_XmlAni;
// typedef std::list<CJAnimation*>::iterator	STL_LIST_ITER_XmlAni;

// struct foUpdateXMLAnimation
// {
// 	cocos2d::float dt;
// 
// 	foUpdateXMLAnimation(cocos2d::float dt) : dt( dt ){}
// 	//inline void operator() (CJAnimation* pXmlAni){ pXmlAni->updateFrame( dt ); }
// };


// #define IsStringEqual_CJFlash( std_string_obj, t_string )		std_string_obj.compare( t_string ) == 0
// #define GetAnimationName_CJFlash( std_vector_src, index )		std_vector_src[index]->getAnimationName()


#endif //__CJH_ANIMATION_H__