#include <iostream>
#include <string>
using namespace std;

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
            } 
            else if (isdigit(c)) { 
                encodedText += '9' - (c - '0');
            } 
            else { 
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
            } 
            else if (isdigit(c)) { 
               
                decodedText += '9' - (c - '0');
            } 
            else { 
                decodedText += static_cast<char>(c - 3);
            }
        }
        return decodedText;
    }
};

int main() {
    Cipher cipher;

   

    string inputText;
    cout << "Input Text: ";
    getline(cin, inputText);

    string encodedText = cipher.encode(inputText);
    cout << "Encoded text: " << encodedText << endl;

    string decodedText = cipher.decode(encodedText);
    cout << "Decoded text: " << decodedText << endl;

    return 0;
}
