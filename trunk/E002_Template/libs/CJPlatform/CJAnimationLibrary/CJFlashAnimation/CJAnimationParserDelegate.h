//
//  CJAnimationParserDelegate.h
//  Think
//
//  Created by pdj1117 on 14. 1. 23..
//  Copyright CJ Educations 2014. All rights reserved.
//

#ifndef CJAnimationParserDelegate_h
#define CJAnimationParserDelegate_h

#include "cocos2d.h"

USING_NS_CC;

class CJAnimationParserDelegate
{
public:
    
public:
	virtual void begin(){}                          /* override me */
    virtual void parseThreadStartCallback(){}       /* override me */
	virtual void parseThreadEndCallback(){}         /* override me */
    virtual void end(){}                            /* override me */
};

#endif
