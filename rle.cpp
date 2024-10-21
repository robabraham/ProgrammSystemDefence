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
            encoded += input[i] + to_string(count);
        }
        return encoded;
    }
};

int main() {
    string input;
    cout << "Enter a string to encode: ";
    cin >> input;
    RLE rle;

    string encoded = rle.encode(input);
    cout << "Encoded string: " << encoded << endl;

    return 0;
}
