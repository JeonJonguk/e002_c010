//
//  THObjectivePayment.h
//  Think
//
//  Created by pureye4u BX on 12. 7. 2..
//  Copyright CJ Educations 2012. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <StoreKit/StoreKit.h>
#include "THPayment.h"

@interface THObjectivePayment : NSObject <SKProductsRequestDelegate, SKPaymentTransactionObserver>{
	BOOL m_isEnabeld;
	BOOL m_isCheckInfoProcessing;
	BOOL m_isPaymentProcessing;
	BOOL m_isConnected;
	THPayment *m_payment;
	SKProductsRequest *m_preq;
//	NSString *m_productID;
	NSMutableArray *m_products;
	std::vector<std::string> m_restored;
	NSInteger m_paymentMode;
}

@property (readonly)BOOL isCheckInfoProcessing;
@property (readonly)BOOL isPaymentProcessing;
@property (readonly)BOOL isConnected;

-(id)init;
-(void)setDelegate:(THPayment *)delegate;
-(void)stopCheckInfo;
-(void)checkInfo:(NSString *)productID;
-(void)restore:(NSString *)productID;
-(void)restoreAll:(std::vector<std::string>)products;
-(void)pay:(NSString *)productID;
-(void)stopPayment;
-(void)completeTransaction:(SKPaymentTransaction *)transaction;
-(void)failedTransaction:(SKPaymentTransaction *)transaction;
-(void)restoreTransaction:(SKPaymentTransaction *)transaction;
-(void)cancelRestore;

@end
