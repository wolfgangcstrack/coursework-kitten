/*
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file contains UserDecryptor class, used to decrypt the user data
represented by the xml files in this lab.
*/

#ifndef USER_DECRYPTOR_H_
#define USER_DECRYPTOR_H_

#include "UserEncryptionInterface.h"

class UserDecryptor : public UserEncryptionInterface
{
public:
	// constructors and destructor
	UserDecryptor() {}
	~UserDecryptor(){}
	// overloaded methods from UserEncryptionInterface
	bool convert(User &user);
	bool convert(std::string &line);
};

#endif // USER_DECRYPTOR_H_