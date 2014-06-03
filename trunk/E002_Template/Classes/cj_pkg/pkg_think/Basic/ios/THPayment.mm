//
//  THPayment.cpp
//  Think
//
//  Created by pureye4u BX on 12. 7. 2..
//  Copyright CJ Educations 2012. All rights reserved.
//

#include "THPayment.h"
#include "THObjectivePayment.h"

THPayment *s_defaultPayment = NULL;
THObjectivePayment *s_defaultObjectivePayment = nil;

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
	if(s_defaultObjectivePayment == nil)
	{
		s_defaultObjectivePayment = [[THObjectivePayment alloc] init];
		[s_defaultObjectivePayment setDelegate:this];
	}
//	m_productID = "";
	
	return true;
}

void THPayment::setDelegate(THPaymentDelegate *delegate)
{
	m_delegate = delegate;
}

void THPayment::checkInfo(const char *pszProductID)
{
	if([s_defaultObjectivePayment isCheckInfoProcessing] && m_productID.compare(pszProductID) != 0)
	{
		// Cancel
		[s_defaultObjectivePayment stopCheckInfo];
	}
	m_productID = pszProductID;
	[s_defaultObjectivePayment checkInfo:[NSString stringWithCString:m_productID.c_str() encoding:NSUTF8StringEncoding]];
}

void THPayment::restoreInApp(const char *pszProductID)
{
	m_productID = pszProductID;
	[s_defaultObjectivePayment restore:[NSString stringWithCString:m_productID.c_str() encoding:NSUTF8StringEncoding]];
}

void THPayment::restoreAllInApp(std::vector<std::string> products)
{
	[s_defaultObjectivePayment restoreAll:products];
}

void THPayment::payInApp(const char *pszProductID)
{
	m_productID = pszProductID;
	[s_defaultObjectivePayment pay:[NSString stringWithCString:m_productID.c_str() encoding:NSUTF8StringEncoding]];
}

void THPayment::cancelPay()
{
	[s_defaultObjectivePayment stopPayment];
}

void THPayment::cancelAll()
{
	[s_defaultObjectivePayment stopCheckInfo];
	[s_defaultObjectivePayment stopPayment];
	
}

bool THPayment::getIsConnected()
{
	return (bool)[s_defaultObjectivePayment isConnected];
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

