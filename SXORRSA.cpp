#include "SXORRSA.h"

bool SXORRSA::is_prime(unsigned int n)
{
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (unsigned int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

unsigned int SXORRSA::generate_prime(unsigned int min, unsigned int max)
{
    unsigned int p = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(min, max);

    while (!this->is_prime(p)) {
        p = dist(gen);
    }

    return p;
}

unsigned int SXORRSA::gcd(unsigned int a, unsigned int b)
{
    if (a == 0) return b;
    if (b == 0) return a;
    if (a == b) return a;
    if (a > b) return this->gcd(a - b, b);
    return this->gcd(a, b - a);
}

unsigned int SXORRSA::powmod(unsigned int a, unsigned int b, unsigned int m)
{
    unsigned int result = 1;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % m;
        }
        a = (a * a) % m;
        b = b / 2;
    }
    return result;
}

string SXORRSA::toASCII(int number)
{
    std::ostringstream result;
    result << std::setfill('0') << std::setw(8) << std::oct << number;
    return result.str();
}

int SXORRSA::fromASCII(string asciiString)
{
    int result = std::stoi(asciiString, nullptr, 8);
    return result;
}

vector<pair<unsigned int, unsigned int>> SXORRSA::Gen_RSA_Keys()
{
    vector<unsigned int> keys = this->generate_keypair();
    pair<unsigned int, unsigned int> publicKey;
    pair<unsigned int, unsigned int> privateKey;

    publicKey.first = keys[0]; publicKey.second = keys[2];
    privateKey.first = keys[1]; privateKey.second = keys[2];

    vector<pair<unsigned int, unsigned int>> keyPairs;
    keyPairs.push_back(publicKey);
    keyPairs.push_back(privateKey);

    return keyPairs;
}

string SXORRSA::getXorKey()
{
    return this->xorKey;
}

unsigned int SXORRSA::getP()
{
    return this->p;
}

unsigned int SXORRSA::getQ()
{
    return this->q;
}

SXORRSA::SXORRSA()
{
    this->xorKey = generate_random_string(10);
}

SXORRSA::~SXORRSA()
{

}

vector<unsigned int> SXORRSA::generate_keypair()
{
    this->p = this->generate_prime(10, 100);
    this->q = this->generate_prime(10, 100);

    vector<unsigned int> keys;
    unsigned int n = this->getP() * this->getQ();
    unsigned int phi = (this->getP() - 1) * (this->getQ() - 1);
    unsigned int e = 0;
    unsigned int d = 0;

    // ���������� �������� ����
    while (true) {
        e = generate_prime(2, phi - 1);
        if (gcd(e, phi) == 1) break;
    }

    // ��������� ��������� ����
    unsigned int k = 1;
    while (true) {
        k += phi;
        if (k % e == 0) {
            d = k / e;
            break;
        }
    }


    keys.push_back(e); // �������� ����
    keys.push_back(d); // ��������� ����
    keys.push_back(n); // ������

    return keys;
}

string SXORRSA::xorEncryptDecrypt(string text, bool flag, string xorKey)
{
    string result = "";
    int text_length = text.length();
    int key_length = xorKey.length();

    for (int i = 0; i < text_length; i++) {
        result += text[i] ^ xorKey[i % key_length];
    }

    if (flag) {
        result += "-" + xorKey;
    }

    return result;
}

string SXORRSA::xorEncryptDecrypt(string text, bool flag)
{
    string result = "";
    int text_length = text.length();
    int key_length = this->getXorKey().length();

    for (int i = 0; i < text_length; i++) {
        result += text[i] ^ this->getXorKey()[i % key_length];
    }

    if (flag) {
        result += "-" + this->getXorKey();
    }

    return result;
}

string SXORRSA::generate_random_string(int length) {
    static std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_int_distribution<int> dist(0, charset.length() - 1);
    std::string result;
    result.reserve(length);
    for (int i = 0; i < length; i++) {
        result += charset[dist(gen)];
    }
    return result;
}

vector<unsigned int> SXORRSA::encrypt(string message, unsigned int e, unsigned int n)
{
    vector<unsigned int> ciphertext;
    for (char c : message) {
        unsigned int m = c;
        unsigned int cT = powmod(m, e, n);
        ciphertext.push_back(cT);
    }
    return ciphertext;
}

string SXORRSA::decrypt(vector<unsigned int> ciphertext, unsigned int d, unsigned int n)
{
    stringstream ss;
    for (unsigned int c : ciphertext) {
        unsigned int m = powmod(c, d, n);
        ss << (char)m;
    }
    return ss.str();
}
