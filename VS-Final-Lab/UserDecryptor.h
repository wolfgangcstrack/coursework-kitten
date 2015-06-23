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
private:
	void decrypt(); // decrypts whatever is stored in this->cache
public:
	// constructors and destructor
	UserDecryptor() {}
	~UserDecryptor(){}
	// overloaded methods from UserEncryptionInterface
	void convert(User &user);
	void convert(std::string &line);
};

void UserDecryptor::decrypt()
{
	for (size_t index = 0; index < cache.length(); index++)
	{
		if (index % 2 == 0)
			cache[index] += OFFSET_EVEN;
		else
			cache[index] -= OFFSET_ODD;
	}
}

void UserDecryptor::convert(User &user)
{
	cache = user.getLastName();
	this->decrypt();
	user.setLastName(cache);

	cache = user.getFirstName();
	this->decrypt();
	user.setFirstName(cache);

	user.setAsDecrypted();
}

void UserDecryptor::convert(std::string &line)
{
	cache = line;
	this->decrypt();
	line = cache;
}

#endif // USER_DECRYPTOR_H_