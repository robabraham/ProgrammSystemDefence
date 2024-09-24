#include <iostream>
#include <string>
using namespace std;

int main() {
    char alphabet[26];
    char reverseAlphabet[26];
    
    for (int i = 0; i < 26; i++) {
        alphabet[i] = 'A' + i;
        reverseAlphabet[i] = 'Z' - i;
    }
    
    cout << "Alphabet: ";
    for (int i = 0; i < 26; i++) {
        cout << alphabet[i] << " ";
    }
    cout << endl;
    
    cout << "Reverse Alphabet: ";
    for (int i = 0; i < 26; i++) {
        cout << reverseAlphabet[i] << " ";
    }
    cout << endl;
    
    string inputText;
    cout << "Input Text: ";
    getline(cin, inputText);

    string encodedText = "";
    for (char c : inputText) {
        if (isalpha(c)) {  
            if (isupper(c)) {
                encodedText += reverseAlphabet[c - 'A']; 
            } else {
                encodedText += tolower(reverseAlphabet[c - 'a']);  
            } 
        } else {
            encodedText += c;
        }
    }
    cout << "Encode text: " << encodedText << endl;

    return 0;
}
