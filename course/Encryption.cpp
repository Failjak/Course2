#include "Encryption.h"

std::vector<int> Encrypt::key = {1, 2, 3, 4, 5, 6, 7, 8};

std::wstring Encrypt::encrypt(std::wstring text)
{
	int len = text.length();
	wchar_t * encr_text = new wchar_t[len + 1];
	encr_text[len] = '\0';

	for (int i = 0; i < len; i++) {
		encr_text[i] = text[i] ^ key.at(i);
	}

	return std::wstring(encr_text);
}

std::wstring Encrypt::decrypt(std::wstring text)
{
	int len = text.length();
	wchar_t * decr_text = new wchar_t[len + 1];
	decr_text[len] = '\0';

	for (int i = 0; i < len; i++) {
		decr_text[i] = text[i] ^ key.at(i);
	}

	return std::wstring(decr_text);
}
