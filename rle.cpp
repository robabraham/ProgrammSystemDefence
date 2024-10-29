#include <iostream>
#include <string>

using namespace std;

class RLE {
public:
    RLE() {}

    string encode(const string& input) {
        string encoded = "";
        int n = input.length();

        for (int i = 0; i < n; i++) {
            int count = 1;
            while (i < n - 1 && input[i] == input[i + 1]) {
                count++;
                i++;
            }
            encoded += input[i]; 
            encoded += to_string(count);
        }
        return encoded;
    }

    string decode(const string& encoded) {
        string decoded = "";
        int n = encoded.length();

        for (int i = 0; i < n; i++) {
            char ch = encoded[i]; 
            i++;
            int count = 0;
            while (i < n && isdigit(encoded[i])) {
                count = count * 10 + (encoded[i] - '0'); 
                i++;
            }
            i--; 
            decoded.append(count, ch); 
        }
        return decoded;
    }
};

int main() {
    string input;
    cout << "Enter a string to encode: ";
    cin >> input;

    RLE rle;
    string encoded = rle.encode(input);
    cout << "Encoded string: " << encoded << endl;

    string decoded = rle.decode(encoded);
    cout << "Decoded string: " << decoded << endl;

    return 0;
}
