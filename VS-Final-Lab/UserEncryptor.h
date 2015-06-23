/*
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file contains UserEncryptor class, used to encrypt the user data
represented by the xml files in this lab.
*/

#ifndef USER_ENCRYPTOR_H_
#define USER_ENCRYPTOR_H_

#include "UserEncryptionInterface.h"

class UserEncryptor : public UserEncryptionInterface
{
public:
	// constructors and destructor
	UserEncryptor() {}
	~UserEncryptor(){}
	// overloaded methods from UserEncryptionInterface
	bool convert(User &user);
	bool convert(std::string &line);
};

#endif // USER_ENCRYPTOR_H_