//
//  CJNarrationIos.m
//  SoundPhonics_Template
//
//  Created by SangSeong Lee on 6/20/13.
//
//

#import "CJUriConnection.h"

@implementation CJUri

+ (void)showBrowser:(std::string)pszURL
{
    NSURL *url = [NSURL URLWithString:[NSString stringWithUTF8String:pszURL.c_str()]];
    [[UIApplication sharedApplication] openURL:url];
}

@end
