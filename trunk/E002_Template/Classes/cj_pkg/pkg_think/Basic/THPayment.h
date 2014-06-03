//
//  THPayment.h
//  Think
//
//  Created by pureye4u BX on 12. 7. 2..
//  Copyright CJ Educations 2012. All rights reserved.
//

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#ifndef Think_THPayment_h
#define Think_THPayment_h

#include "THPaymentDelegate.h"
#include <string>
#include <vector>

class THPayment
{
public:
	static THPayment *defaultPayment();
	bool init();
	void setDelegate(THPaymentDelegate *delegate);
	void checkInfo(const char *pszProductID);
	void restoreInApp(const char *pszProductID);
	void restoreAllInApp(std::vector<std::string> products);
	void payInApp(const char *pszProductID);
	void cancelPay();
	void cancelAll();
	THPayment *getDefaultPayment();
	bool getIsConnected();
	
	virtual void hndDidReceiveInfo(const char *name, const char *description, const char *price);
	virtual void hndCompleteTransaction();
	virtual void hndFailedTransaction();
	virtual void hndRestoreTransaction();
	virtual void hndRestoreTransaction(std::vector<std::string> products);
	virtual void hndCancelRestore();
	
private:
	std::string m_productID;
	THPaymentDelegate *m_delegate;
	
};

#endif
#endif
