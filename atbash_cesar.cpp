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

class Cipher {
private:
    char alphabet[26];
    char reverseAlphabet[26];

public:
    Cipher() {
        for (int i = 0; i < 26; i++) {
            alphabet[i] = 'A' + i;
            reverseAlphabet[i] = 'Z' - i;
        }
    }

    string encode(const string& inputText) const {
        string encodedText = "";
        for (char c : inputText) {
            if (isalpha(c)) {
                if (isupper(c)) {
                    encodedText += reverseAlphabet[c - 'A'];
                } else {
                    encodedText += tolower(reverseAlphabet[c - 'a']);
                }
            } else if (isdigit(c)) {
                encodedText += '9' - (c - '0');
            } else {
                encodedText += static_cast<char>(c + 3);
            }
        }
        return encodedText;
    }

    string decode(const string& encodedText) const {
        string decodedText = "";
        for (char c : encodedText) {
            if (isalpha(c)) {
                if (isupper(c)) {
                    decodedText += alphabet['Z' - c];
                } else {
                    decodedText += tolower(alphabet['z' - c]);
                }
            } else if (isdigit(c)) {
                decodedText += '9' - (c - '0');
            } else {
                decodedText += static_cast<char>(c - 3);
            }
        }
        return decodedText;
    }
};

int main() {
    CaesarCipher caesarCipher;
    Cipher cipher;

    string inputText;
    int shift;

    cout << "Input text: ";
    getline(cin, inputText);
    cout << "Input Caesar shift value: ";
    cin >> shift;
    cin.ignore();  

    string encodedWithSecondCipher = cipher.encode(inputText);
    cout << "Encoded with Atbash: " << encodedWithSecondCipher << endl;

    string encryptedWithCaesar = caesarCipher.encrypt(encodedWithSecondCipher, shift);
    cout << "Encrypted with Caesar cipher: " << encryptedWithCaesar << endl;

    string decryptedWithCaesar = caesarCipher.decrypt(encryptedWithCaesar, shift);
    cout << "Decrypted with Caesar cipher: " << decryptedWithCaesar << endl;

    // Step 4: Decode the result using the second cipher
    string decodedWithSecondCipher = cipher.decode(decryptedWithCaesar);
    cout << "Decoded with Atbash cipher: " << decodedWithSecondCipher << endl;

    return 0;
}
