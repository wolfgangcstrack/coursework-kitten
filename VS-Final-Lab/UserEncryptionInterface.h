/*
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file contains the UserEncryptionInterface, which manages shared
variables/methods for any class that implements this interface.
*/

#ifndef USER_ENCRYPTION_INTERFACE_
#define USER_ENCRYPTION_INTERFACE_

#include "User.h"
#include <string>

class UserEncryptionInterface
{
protected:
	static const int OFFSET_EVEN = 33;
	static const int OFFSET_ODD = 132;

	std::string cache;
public:
	virtual const std::string & getCache() { return cache; }
	virtual void convert(User &user) = 0;
	virtual void convert(std::string &line) = 0;
};

#endif // USER_ENCRYPTION_INTERFACE_