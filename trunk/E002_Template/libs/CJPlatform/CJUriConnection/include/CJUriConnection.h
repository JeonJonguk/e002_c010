 

#pragma once

#include "cocos2d.h"


USING_NS_CC;  


class CJUriConnection
{

public:
     
    CJUriConnection();
    ~CJUriConnection();

    
    
    /**
     @brief Get the shared Engine object,it will new one when first time be called
     */
    static CJUriConnection* getInstance();
    
    /**
     @brief Release the shared Engine object
     @warning It must be called before the application exit, or a memroy leak will be casued.
     */
     
    void  showBrowser(std::string pszURL); 
     
};

