#include <iostream>
#include <string>
using namespace std;

class CaesarCipher {
public:
    string encrypt(string text, int shift) {
        string result = "";

        for (int i = 0; i < text.length(); i++) {
            char ch = text[i];

            if (ch >= 'a' && ch <= 'z') {
                result += char(int('a' + (ch - 'a' + shift) % 26));
            } else if (ch >= 'A' && ch <= 'Z') {
                result += char(int('A' + (ch - 'A' + shift) % 26));
            } else if (ch >= '0' && ch <= '9') {
                result += char(int('0' + (ch - '0' + shift) % 10));  
            } else {
                result += char(int(ch + shift) % 128);  
            }
        }
        return result;
    }

    string decrypt(string text, int shift) {
        return encrypt(text, -1*shift);  
    }
};

int main() {
    CaesarCipher cipher;
    string text;
    int shift;

    cout << "Input text: ";
    getline(cin, text);
    cout << "Input shift value: ";
    cin >> shift;

    string encryptedText = cipher.encrypt(text, shift);
    cout << "Encrypted text: " << encryptedText << endl;

    string decryptedText = cipher.decrypt(encryptedText, shift);
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}
