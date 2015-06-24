/*
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file contains UserEncryptor class, used to encrypt the user data
represented by the xml files in this lab. While this file is not
included in main.cpp, it can be used to reencrypt data that has been
decrypted by the UserDecryptor class.
*/

#ifndef USER_ENCRYPTOR_H_
#define USER_ENCRYPTOR_H_

#include "UserEncryptionInterface.h"
#include <string>

class UserEncryptor : public UserEncryptionInterface
{
private:
	void encrypt(); // encrypts whatever is stored in this->buffer
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
	for (size_t index = 0; index < buffer.length(); index++)
	{
		if (index % 2 == 0)
			buffer[index] -= OFFSET_EVEN;
		else
			buffer[index] += OFFSET_ODD;
	}
}

void UserEncryptor::convert(User &user)
{
	buffer = user.getLastName();
	this->encrypt();
	user.setLastName(buffer);

	buffer = user.getFirstName();
	this->encrypt();
	user.setFirstName(buffer);

	user.setAsEncrypted();
}

void UserEncryptor::convert(std::string &line)
{
	buffer = line;
	this->encrypt();
	line = buffer;
}

#endif // USER_ENCRYPTOR_H_