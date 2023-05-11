# Simple_XOR_RSA_KeyGenerator

1. Gen_RSA_Keys() - returns vector<pair<unsigned int, unsigned int>> ([publicKey, module], [privateKey, module])
2. Further, if you wish, you can additionally encrypt this keys with: 
  - toASCII() - takes int Key, returns string where each character is converted to an ASCII code,     accordingly, the fromASCII() function takes a string and returns an int key
  - XorEncryptDecrypt() - takes a string key encrypted with the toASCII() function, and returns       encrypted with XOR string, or decrypted string if you apply this funktion again.
3. Accordingly, if you additionally encrypted the key, you must restore it to its original state before using it.
4. encrypt() function takes a string - a message, unsigned int - a public key and a module, respectively, if we have a vector<pair<unsigned int, unsigned int>> Keys, then the public key is keys[0].first and its module keys[0].second, private key keys[1].first and keys[1].second by analogy. This function returns a vector<unsigned int> - an encrypted message, each element of the vector is a number
5. decrypt() function takes a vector<unsigned int> - a encrypted message, unsigned int - a private key, and a module. This function returns a string - decrypted message.

# Usage example:

#include "SXORRSA.h"
  
SXORRSA simpleXorRSA;
vector<pair<unsigned int, unsigned int>> keys = simpleXorRSA.Gen_RSA_Keys();
  
std::string msg = "HelloWorld!";
vector<unsigned int> encryptedMsg = simpleXorRSA.encrypt(msg, keys[0].first, keys[0].second);
std::cout << "Encrypted msg = " << encryptedMsg << std::endl;
  
std::string decryptedMsg = simpleXorRSA.decrypt(encryptedMsg, keys[1].first, keys[1].second);
std::cout << "Decrypted msg = " << decryptedMsg << std::endl;
