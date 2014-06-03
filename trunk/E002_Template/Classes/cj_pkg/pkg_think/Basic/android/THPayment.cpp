//
//  THPayment.cpp
//  Think
//
//  Created by pureye4u BX on 12. 7. 2..
//  Copyright CJ Educations 2012. All rights reserved.
//

#include "THPayment.h"

THPayment *s_defaultPayment = NULL;

THPayment *THPayment::defaultPayment()
{
	if(s_defaultPayment == NULL)
	{
		s_defaultPayment = new THPayment();
		s_defaultPayment->init();
	}
	
	return s_defaultPayment;
}

bool THPayment::init()
{
	
	
	return true;
}

void THPayment::setDelegate(THPaymentDelegate *delegate)
{
	m_delegate = delegate;
}

void THPayment::checkInfo(const char *pszProductID)
{
	
}

void THPayment::restoreInApp(const char *pszProductID)
{
	m_productID = pszProductID;
}

void THPayment::restoreAllInApp(std::vector<std::string> products)
{
	
}

void THPayment::payInApp(const char *pszProductID)
{
	m_productID = pszProductID;
}

void THPayment::cancelPay()
{
	
}

void THPayment::cancelAll()
{
	
}

bool THPayment::getIsConnected()
{
	return true;
}

void THPayment::hndDidReceiveInfo(const char *name, const char *description, const char *price)
{
	m_delegate->hndDidReceiveInfo(name, description, price);
}

void THPayment::hndCompleteTransaction()
{
	m_delegate->hndCompleteTransaction();
}

void THPayment::hndFailedTransaction()
{
	m_delegate->hndFailedTransaction();
}

void THPayment::hndRestoreTransaction()
{
	m_delegate->hndRestoreTransaction();
}

void THPayment::hndRestoreTransaction(std::vector<std::string> products)
{
	m_delegate->hndRestoreTransaction(products);
}

void THPayment::hndCancelRestore()
{
	m_delegate->hndCancelRestore();
}

