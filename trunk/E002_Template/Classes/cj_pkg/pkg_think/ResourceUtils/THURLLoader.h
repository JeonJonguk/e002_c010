//
//  THURLLoader.h
//  ithink
//
//  Created by pureMini on 13. 2. 4..
//
//

#ifndef __ithink__THURLLoader__
#define __ithink__THURLLoader__

#include "THURLRequestDelegate.h"
#include <string>
#include <vector>

typedef struct THDictionary
{
	const char *key;
	const char *value;
}THDictionary;

typedef enum
{
	kTHURLLoaderMethodGet,
	kTHURLLoaderMethodPost,
}kTHURLLoaderMethod;


class THURLLoader
{
public:
	// Member
	
	// Mehod
	
	THURLLoader();
	virtual ~THURLLoader();
	bool init();
	bool initWithURL(const char *pszURL = NULL);
	
	void setHeader(std::vector<THDictionary>);
	void setMethod(int iMethodType);
	void setData(std::vector<THDictionary>);
	void setURL(const char *pszURL);
	void load(const char *pszURL = NULL);
	
protected:
	// Member
	
	std::string m_sURL;
	int m_iMethodType;
	std::vector<THDictionary> m_vtHeader;
	std::vector<THDictionary> m_vtData;
	
	THURLRequestDelegate *m_pDelegate;
	
	
	// Mehod
	
	static void *runLoad(void *);
	
	virtual void complete(const char *pszData);
	virtual void error(int iType, const char *pszDescription);
	
};

#endif /* defined(__ithink__THURLLoader__) */
