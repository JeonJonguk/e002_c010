//
//  CJUriConnection.m
//  E001_C010_iphone
//
//  Created by j2enty on 2013. 12. 4..
//
//

#import "CJUriConnection.h"
#import "CJUri.h"

static CJUriConnection *s_uriConnection;

CJUriConnection::CJUriConnection()
{
    
}

CJUriConnection::~CJUriConnection()
{
    
}

CJUriConnection* CJUriConnection::getInstance()
{
    if (!s_uriConnection)
    {
        s_uriConnection = new CJUriConnection();
    }
    
    return s_uriConnection;
}




void CJUriConnection::showBrowser(std::string pszURL)
{
    [CJUri showBrowser:pszURL];
}
