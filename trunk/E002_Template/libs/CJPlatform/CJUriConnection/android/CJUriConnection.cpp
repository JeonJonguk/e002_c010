 

#include "../include/CJUriConnection.h"
#include "jni/CJUriConnectionJni.h" 

static CJUriConnection * s_pInstance = 0;

CJUriConnection::CJUriConnection()
{
    
}

CJUriConnection::~CJUriConnection()
{

}

CJUriConnection* CJUriConnection::getInstance()
{
    if (! s_pInstance)
    {
        s_pInstance = new CJUriConnection();
    }
    
    return s_pInstance;
}

void CJUriConnection::showBrowser(std::string pszURL)
{
    showBrowserConnectionJNI(pszURL.c_str());
}
 
