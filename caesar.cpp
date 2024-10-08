#include <iostream>
#include <string>
using namespace std;

string caesar(string text, int shift) {
    string result = "";

    for (int i = 0; i < text.length(); i++) {
        char ch = text[i];

        if (ch >= 'a' && ch <= 'z') {
            result += char(int('a' + (ch - 'a' + shift) % 26));
        }
 
        else if (ch >= 'A' && ch <= 'Z') {
            result += char(int('A' + (ch - 'A' + shift) % 26));
        }
    }
    return result;
}

int main() {
    string text;
    int shift;

    
    cout << "Input text:";
    getline(cin, text);
    cout << "Input number: ";
    cin >> shift;


    string enText = caesar(text, shift);
    cout << "Encrypted text: " << enText<<endl;

    return 0;
}
