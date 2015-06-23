/*
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file contains UserEncryptor class, used to encrypt the user data
represented by the xml files in this lab.
*/

#ifndef USER_ENCRYPTOR_H_
#define USER_ENCRYPTOR_H_

#include "UserEncryptionInterface.h"
#include <string>

class UserEncryptor : public UserEncryptionInterface
{
private:
	void encrypt(); // encrypts whatever is stored in this->cache
public:
	// constructors and destructor
	UserEncryptor() {}
	~UserEncryptor(){}
	// overloaded methods from UserEncryptionInterface
	void convert(User &user);
	void convert(std::string &line);
};

void UserEncryptor::encrypt()
{
	for (size_t index = 0; index < cache.length(); index++)
	{
		if (index % 2 == 0)
			cache[index] -= OFFSET_EVEN;
		else
			cache[index] += OFFSET_ODD;
	}
}

void UserEncryptor::convert(User &user)
{
	cache = user.getLastName();
	this->encrypt();
	user.setLastName(cache);

	cache = user.getFirstName();
	this->encrypt();
	user.setFirstName(cache);
}

void UserEncryptor::convert(std::string &line)
{
	cache = line;
	this->encrypt();
	line = cache;
}

#endif // USER_ENCRYPTOR_H_