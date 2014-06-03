//
//  CJLMSExtension_objc.h
//  S001_Template
//
//  Created by Soonho Hong on 12. 11. 8..
//
//

#import <Foundation/Foundation.h>

/**
 * @author CJEducations
 * @brief cjextension connect on ios
 * @version v1.0.0
 * @date 2012. 11. 20
 * @since v1.0.0
 */
@interface CJLMSExtension_objc : NSObject {
    
}

/**
 * @author CJEducations
 * @brief get current date&time on ios device
 * @version v1.0.0
 * @return date&time string value (NSString*)
 * @date 2012. 11. 20
 * @since v1.0.0
 */
-(NSString*) getDeviceDateTime;

/**
 * @author CJEducations
 * @brief get complete date&time on ios device
 * @version v1.0.0
 * @param packageIndex : package define number (NSInteger)
 * @return date&time string value (NSString*)
 * @date 2012. 11. 20
 * @since v1.0.0
 */
-(NSString*) getTargetDateTime:(NSInteger) packageIndex;

+ (CJLMSExtension_objc*) sharedEngine;

+(void) end;

@end
