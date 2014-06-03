//
//  THStringUtil.h
//  Think
//
//  Created by pureye4u BX on 12. 6. 18..
//  Copyright CJ Educations 2012. All rights reserved.
//

#ifndef Think_THStringUtil_h
#define Think_THStringUtil_h

#include <stdarg.h> 
#include <iostream>
#include <vector>

class THStringUtil
{
public:
	static std::string format(const char *fmt, ...);
	static std::vector<std::string> split(const char *str, char c = ' ');
	static std::string base64_encode(unsigned char const *bytes_to_encode, unsigned int in_len);
	static std::string urlencode(const std::string &c);
	static std::string replaceAll(const std::string &str, const std::string &ptn, const std::string &replace);
	static std::string stringWithComma(const std::string &str, unsigned int intval);
private:
	static std::string format_arg_list(const char *fmt, va_list args);
	static std::string char2hex(char dec);
	static inline bool is_base64(unsigned char c);
};

#endif
