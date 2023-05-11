#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <random>
#include <vector>
#include <utility>
#include <sstream>
#include <iomanip>

using namespace std;

class SXORRSA {

private:
	string xorKey;
	unsigned int p;
	unsigned int q;

	bool is_prime(unsigned int);
	unsigned int generate_prime(unsigned int, unsigned int);
	unsigned int gcd(unsigned int, unsigned int);
	unsigned int powmod(unsigned int, unsigned int, unsigned int);

	vector<unsigned int> generate_keypair();
	string generate_random_string(int);

	string getXorKey();
	unsigned int getP();
	unsigned int getQ();

public:
	SXORRSA();
	virtual ~SXORRSA();

	string xorEncryptDecrypt(string, bool);
	string xorEncryptDecrypt(string, bool, string);

	string toASCII(int);
	int fromASCII(string);

	vector<pair<unsigned int, unsigned int>> Gen_RSA_Keys();

	vector<unsigned int> encrypt(string, unsigned int, unsigned int);
	string decrypt(vector<unsigned int>, unsigned int, unsigned int);

};