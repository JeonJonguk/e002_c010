
//
//  THObjectivePayment.cpp
//  Think
//
//  Created by pureye4u BX on 12. 7. 2..
//  Copyright CJ Educations 2012. All rights reserved.
//

#import "THObjectivePayment.h"
#import "THPayment.h"

enum
{
	kPaymentModePay,
	kPaymentModeRestore,
	kPaymentModeRestoreAll,
};

@implementation THObjectivePayment

@synthesize isCheckInfoProcessing = m_isCheckInfoProcessing;
@synthesize isPaymentProcessing = m_isPaymentProcessing;
@synthesize isConnected = m_isConnected;

-(id)init
{
	if((self = [super init]) != nil)
	{
		// Initialize
		m_isEnabeld = YES;
		m_isCheckInfoProcessing = NO;
		m_isPaymentProcessing = NO;
		m_isConnected = NO;
		m_payment = NULL;
		m_products = [[NSMutableArray alloc] init];
		m_restored = std::vector<std::string>();
	}
	
	return self;
}

-(void)setDelegate:(THPayment *)delegate
{
	m_payment = delegate;
}

-(void)stopCheckInfo
{
	if(m_preq != nil)
	{
		[m_preq cancel];
		m_preq = nil;
	}
	m_isCheckInfoProcessing = NO;
}

-(void)stopPayment
{
	if(m_isPaymentProcessing)
	{
		m_isPaymentProcessing = NO;
	}
	
	m_isEnabeld = NO;
}

-(void)checkInfo:(NSString *)productID
{
	if(m_isCheckInfoProcessing)
	{
		[self stopCheckInfo];
	}
	
	m_preq = [[SKProductsRequest alloc] initWithProductIdentifiers:[NSSet setWithObject:productID]];
	[m_preq setDelegate:self];
	m_isCheckInfoProcessing = YES;
	[m_preq start];
}

-(void)pay:(NSString *)productID
{
	m_paymentMode = kPaymentModePay;
	m_isEnabeld = YES;
	
	if(!m_isConnected)
	{
		[[SKPaymentQueue defaultQueue] addTransactionObserver:self];
		m_isConnected = YES;
	}
	
	@try
	{
		if([SKPaymentQueue canMakePayments])
		{
			SKPayment *payment = [SKPayment paymentWithProductIdentifier:productID];
			[[SKPaymentQueue defaultQueue] addPayment:payment];
		}
	}
	@catch(NSException *e)
	{
//		NSLog(@"pay exception %@: %@", [e name], [e reason]);
	}
}

-(void)restore:(NSString *)productID
{
	m_paymentMode = kPaymentModeRestore;
//	m_productID = [productID copy];
	[m_products removeAllObjects];
	[m_products addObject:[productID copy]];
	m_isEnabeld = YES;
	
	if(!m_isConnected)
	{
		[[SKPaymentQueue defaultQueue] addTransactionObserver:self];
		m_isConnected = YES;
	}
	
	@try
	{
		if([SKPaymentQueue canMakePayments])
		{
			m_isPaymentProcessing = YES;
			[[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
		}
	}
	@catch(NSException *e)
	{
//		NSLog(@"restore exception %@: %@", [e name], [e reason]);
	}
}

-(void)restoreAll:(std::vector<std::string>)products
{
	int l = products.size();
	if(l)
	{
		m_paymentMode = kPaymentModeRestoreAll;
		
		m_restored.clear();
		[m_products removeAllObjects];
		
		for(int i = 0; i < l; i++)
		{
			NSString *productID = [NSString stringWithUTF8String:products[i].c_str()];
			[m_products addObject:productID];
		}
		
		m_isEnabeld = YES;
		
		if(!m_isConnected)
		{
			[[SKPaymentQueue defaultQueue] addTransactionObserver:self];
			m_isConnected = YES;
		}
		
		@try
		{
			if([SKPaymentQueue canMakePayments])
			{
				m_isPaymentProcessing = YES;
				[[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
			}
		}
		@catch(NSException *e)
		{
			NSLog(@"restore all exception %@: %@", [e name], [e reason]);
		}		
	}
}

-(void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue
{
	if(m_paymentMode == kPaymentModeRestore ||
	   m_paymentMode == kPaymentModeRestoreAll)
	{
		if(queue.transactions.count == 0)
		{
			if(m_paymentMode == kPaymentModeRestoreAll)
			{
				[self restoreAllComplete];
			}
			else
			{
				[self cancelRestore];
			}
		}
		else
		{
			BOOL isRestored = NO;
			for(SKPaymentTransaction *transaction in queue.transactions)
			{
				switch([transaction transactionState])
				{
					case SKPaymentTransactionStateRestored:
					{
						NSString *productID = [[transaction payment] productIdentifier];
//						NSLog(@"===== %@", productID);
						NSInteger i = [m_products indexOfObjectPassingTest:^BOOL(id obj, NSUInteger idx, BOOL *stop) {
							return [obj isEqualToString:productID];
						}];
						if(i != NSNotFound)
//						if([[[transaction payment] productIdentifier] isEqualToString:m_productID])
						{
							isRestored = YES;
							if(m_paymentMode == kPaymentModeRestore)
							{
								[self restoreTransaction:transaction];
							}
							else if(m_paymentMode == kPaymentModeRestoreAll)
							{
								[self addRestoreTransaction:transaction forProductID:productID];
							}
						}
						else
						{
							[[SKPaymentQueue defaultQueue] finishTransaction:transaction];
						}
						break;
					}
					default:
						[[SKPaymentQueue defaultQueue] finishTransaction:transaction];
						break;
				}
			}
			if(m_paymentMode == kPaymentModeRestoreAll)
			{
				[self restoreAllComplete];
			}
			else
			{
				if(!isRestored)
				{
					[self cancelRestore];
				}
			}
		}
	}
}

- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error
{
	[self cancelRestore];
}

- (void)cancelRestore
{
	if(m_payment != NULL && m_isEnabeld)
	{
		m_payment->hndCancelRestore();
		m_isEnabeld = NO;
	}
	
	m_isPaymentProcessing = NO;
}

-(void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
	SKProduct *product = [[response products] lastObject];
	if(!product)
	{
		NSLog(@"Error could not find matching products");
		return;
	}
	
	NSNumberFormatter *numberFormatter = [[NSNumberFormatter alloc] init];
	[numberFormatter setFormatterBehavior:NSNumberFormatterBehavior10_4];
	[numberFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
	[numberFormatter setLocale:[product priceLocale]];
	NSString *formattedString = [numberFormatter stringFromNumber:[product price]];
	[numberFormatter release];
	
	
//	NSLog(@"%@", [product localizedTitle]);
//	NSLog(@"%@", [product localizedDescription]);
//	NSLog(@"%@", [product price]);
//	NSLog(@"Price %@", formattedString);
	
	if(m_payment != NULL && m_isCheckInfoProcessing)
	{
		m_payment->hndDidReceiveInfo([[product localizedTitle] cStringUsingEncoding:NSUTF8StringEncoding], [[product localizedDescription] cStringUsingEncoding:NSUTF8StringEncoding], [formattedString cStringUsingEncoding:NSUTF8StringEncoding]);
	}
	
	m_isCheckInfoProcessing = NO;
}

//-(void)paymentQueue:(SKPaymentQueue *)queue removedTransactions:(NSArray *)transactions
//{
//	
//}

-(void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
	if(m_paymentMode == kPaymentModePay)
	{
		for(SKPaymentTransaction *transaction in transactions)
		{
			switch([transaction transactionState])
			{
				case SKPaymentTransactionStatePurchased:
					[self completeTransaction: transaction];
					break;
				case SKPaymentTransactionStateFailed:
					[self failedTransaction: transaction];
					break;
				case SKPaymentTransactionStateRestored:
					[self restoreTransaction: transaction];
					break;
			}
		}
	}
}

-(void)completeTransaction:(SKPaymentTransaction *)transaction
{
	if(m_payment != NULL && m_isEnabeld)
	{
		m_payment->hndCompleteTransaction();
		m_isEnabeld = NO;
	}
	
	m_isPaymentProcessing = NO;
	[[SKPaymentQueue defaultQueue] finishTransaction: transaction];
}

-(void)failedTransaction:(SKPaymentTransaction *)transaction
{
	if(m_payment != NULL && m_isEnabeld)
	{
		m_payment->hndFailedTransaction();
		m_isEnabeld = NO;
	}
	
	m_isPaymentProcessing = NO;
	[[SKPaymentQueue defaultQueue] finishTransaction: transaction];
}

-(void)restoreTransaction:(SKPaymentTransaction *)transaction
{
	if(m_payment != NULL && m_isEnabeld)
	{
		m_payment->hndRestoreTransaction();
		m_isPaymentProcessing = NO;
		m_isEnabeld = NO;
	}
	
	[[SKPaymentQueue defaultQueue] finishTransaction: transaction];
}

-(void)addRestoreTransaction:(SKPaymentTransaction *)transaction forProductID:(NSString *)productID
{
	if(m_payment != NULL && m_isEnabeld)
	{
//		m_payment->hndRestoreTransaction([productID UTF8String]);
		m_restored.push_back([productID UTF8String]);
	}
	
	[[SKPaymentQueue defaultQueue] finishTransaction: transaction];
}

-(void)restoreAllComplete
{
	m_payment->hndRestoreTransaction(m_restored);
	
	m_isPaymentProcessing = NO;
	m_isEnabeld = NO;
}

-(void)dealloc
{
	[m_products release];
	[[SKPaymentQueue defaultQueue] removeTransactionObserver: self];
	
	[super dealloc];
}

@end