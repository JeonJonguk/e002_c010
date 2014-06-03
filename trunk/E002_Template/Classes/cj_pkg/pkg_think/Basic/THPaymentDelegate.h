//
//  THPaymentDelegate.h
//  Think
//
//  Created by pureye4u BX on 12. 7. 2..
//  Copyright CJ Educations 2012. All rights reserved.
//

#ifndef Think_THPaymentDelegate_h
#define Think_THPaymentDelegate_h

#include <string>
#include <vector>

class THPaymentDelegate
{
public:
	virtual void hndDidReceiveInfo(const char *name, const char *description, const char *price){}
	virtual void hndCompleteTransaction(){}
	virtual void hndFailedTransaction(){}
	virtual void hndRestoreTransaction(){}
	virtual void hndRestoreTransaction(std::vector<std::string> products){}
	virtual void hndCancelRestore(){}
};

#endif
