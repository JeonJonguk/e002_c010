//
//  THStringUtil.cpp
//  Think
//
//  Created by pureye4u BX on 12. 6. 18..
//  Copyright CJ Educations 2012. All rights reserved.
//

#include "THStringUtil.h"

// For format string
std::string THStringUtil::format_arg_list(const char *fmt, va_list args)
{
	if(!fmt)
	{
		return "";
	}
	
	int res = -1;
	int l = 256;
	char *buffer = 0;
	
	while(res == -1)
	{
		if(buffer)
		{
			delete [] buffer;
		}
		buffer = new char [l + 1];
		memset(buffer, 0, l + 1);
		res = vsnprintf(buffer, l, fmt, args);
		l *= 2;
	}
	
	std::string s(buffer);
	delete [] buffer;
	return s;
}

// std::string format function
std::string THStringUtil::format(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	std::string s = THStringUtil::format_arg_list(fmt, args);
	va_end(args);
	return s;
}

// std::string split function
std::vector<std::string> THStringUtil::split(const char *str, char c)
{
	std::vector<std::string> res;
	
	while(1)
	{
		const char *begin = str;
		
		while(*str != c && *str)
		{
			str++;
		}
		
		res.push_back(std::string(begin, str));
		
		if(0 == *str++)
		{
			break;
		}
	}
	
	return res;
}

// std::string base64 encoding
static const std::string base64_chars = 
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

inline bool THStringUtil::is_base64(unsigned char c)
{
	return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string THStringUtil::base64_encode(unsigned char const *bytes_to_encode, unsigned int in_len)
{
	std::string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];
	
	while(in_len--)
	{
		char_array_3[i++] = *(bytes_to_encode++);
		if(i == 3)
		{
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;
			
			for(i = 0; i < 4; i++)
			{
				ret += base64_chars[char_array_4[i]];
			}
			i = 0;
		}
	}
	
	if(i)
	{
		for(j = i; j < 3; j++)
		{
			char_array_3[j] = '\0';
		}
		
		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;
		
		for(j = 0; j < i + 1; j++)
		{
			ret += base64_chars[char_array_4[j]];
		}
		
		while(i++ < 3)
		{
			ret += '=';
		}
	}
	
	return ret;
}

// Char to hex
std::string THStringUtil::char2hex(char dec)
{
	char dig1 = (dec & 0xF0) >> 4;
	char dig2 = (dec & 0x0F);
	if(0 <= dig1 && dig1 <= 9) dig1 += 48;
	if(10 <= dig1 && dig1 <= 15) dig1 += 97 - 10;
	if(0 <= dig2 && dig2 <= 9) dig2 += 48;
	if(10 <= dig2 && dig2 <= 15) dig2 += 97 - 10;
	
	std::string ret;
	ret.append(&dig1, 1);
	ret.append(&dig2, 1);
	
	return ret;
}

// Escape characters
std::string THStringUtil::urlencode(const std::string &c)
{
	std::string ret = "";
	int l = c.length();
	for(int i = 0; i < l; i++)
	{
		if((48 <=c[i] && c[i] <= 57) ||
		   (65 <=c[i] && c[i] <= 90) ||
		   (97 <=c[i] && c[i] <= 122) ||
		   (c[i] == '~' || c[i] == '!' || c[i] == '*' || c[i] == '(' || c[i] == ')' || c[i] == '\''))
		{
			ret.append(&c[i], 1);
		}
		else
		{
			ret.append("%");
			ret.append(THStringUtil::char2hex(c[i]));
		}
	}
	
	return ret;
}

std::string THStringUtil::replaceAll(const std::string &str, const std::string &ptn, const std::string &replace)
{
	std::string ret = str;
	std::string::size_type pos = 0;
	std::string::size_type offset = 0;
	
	while((pos = ret.find(ptn, offset)) != std::string::npos)
	{
		ret.replace(ret.begin() + pos, ret.begin() + pos + ptn.size(), replace);
		offset = pos + replace.size();
	}
	
	return ret;
}

std::string THStringUtil::stringWithComma(const std::string &str, unsigned int intval)
{
	std::string sRet;
	int l = str.size();
	int i = l % intval;
	if(i)
	{
		sRet.append(str.substr(0, i));
	}
	while(i < l)
	{
		if(i)
		{
			sRet.append(",");
		}
		sRet.append(str.substr(i, intval));
		i += intval;
	}
	
	return sRet;
}
