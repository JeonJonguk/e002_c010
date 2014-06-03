//
//  NSString+url.m
//  PLAY123-iphone
//
//  Created by yangsoo park on 12. 6. 14..
//  Copyright (c) 2012년 allm. All rights reserved.
//

#import "NSString+url.h"

@implementation NSString (url)
-(NSString *)urlEncodedString {
	
	return [(NSString *)CFURLCreateStringByAddingPercentEscapes(kCFAllocatorDefault, (CFStringRef)self, NULL, CFSTR(":/?#[]@!$&’()*+,;="), -2147481280) autorelease];
	//return [(NSString *)CFURLCreateStringByAddingPercentEscapes(kCFAllocatorDefault, (CFStringRef)self, NULL, CFSTR(":/?#[]@!$&’()*+,;="), kCFStringEncodingUTF8) autorelease];
	
}


-(NSString *)urlDecodedString {
	
	return [self stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
	
}
@end
