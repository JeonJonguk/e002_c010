//
//  CJLMSExtension_objc.m
//  S001_Template
//
//  Created by Soonho Hong on 12. 11. 8..
//
//

#import "CJLMSExtension_objc.h"

#define PN_HAN1    1
#define PN_HAN2    2
#define PN_SAGO    3
#define PN_ENG1    4

@implementation CJLMSExtension_objc

static CJLMSExtension_objc *sharedInstance = nil;

// Init
+ (CJLMSExtension_objc *) sharedEngine
{
    @synchronized(self)     {
        if (!sharedInstance)
            sharedInstance = [[CJLMSExtension_objc alloc] init];
    }
    return sharedInstance;
}

+ (id) alloc
{
    @synchronized(self)     {
        NSAssert(sharedInstance == nil, @"Attempted to allocate a second instance of a singleton.");
        return [super alloc];
    }
    return nil;
}

-(id) init
{
    if((self=[super init])) {
        
    }
    return self;
}

// Memory
- (void) dealloc
{
    [super dealloc];
}

+(void) end
{
    [sharedInstance release];
    sharedInstance = nil;
}

-(NSString*) getDeviceDateTime {
    NSDate* date = [NSDate date];
    NSDateFormatter* formatter = [[[NSDateFormatter alloc] init] autorelease];
    
    [formatter setDateFormat:@"yyyy_MM_dd_HH_mm_ss"];
    
    NSString* rtString = [formatter stringFromDate:date];
    
    return rtString;
}

-(NSString*) getTargetDateTime:(NSInteger) packageIndex {
    NSDate* date = [NSDate date];
    
    NSInteger addTimeVal;
    
    switch (packageIndex) {
        case PN_HAN1:
            addTimeVal = 10;    // complete date val
            break;
        case PN_HAN2:
            addTimeVal = 49;    // complete date val
            break;
        case PN_SAGO:
            addTimeVal = 3;     // complete date val
            break;
        case PN_ENG1:
            addTimeVal = 14*7;
            break;
        default:
            break;
    }
    
    date = [date addTimeInterval:(float)addTimeVal*24*60*60];     // calc second value
    
    NSDateFormatter* formatter = [[[NSDateFormatter alloc] init] autorelease];
    
    [formatter setDateFormat:@"yyyy_MM_dd_HH_mm_ss"];
    
    NSString* rtString = [formatter stringFromDate:date];
    
    return rtString;
}

@end
