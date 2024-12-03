#include <iostream>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

class LZ77Compressor {
public:
    vector<tuple<int, int, char>> compress(const string &input) {
        vector<tuple<int, int, char>> compressedData;
        int windowSize = 8;  
        int bufferSize = 4;  

        int i = 0;
        while (i < input.length()) {
            int longestMatchLength = 0;
            int longestMatchDistance = 0;
            char nextChar = input[i];

            for (int j = max(0, i - windowSize); j < i; ++j) {
                int matchLength = 0;
                while (matchLength < bufferSize && i + matchLength < input.length() && input[j + matchLength] == input[i + matchLength]) {
                    ++matchLength;
                }

                if (matchLength > longestMatchLength) {
                    longestMatchLength = matchLength;
                    longestMatchDistance = i - j;
                    nextChar = (i + matchLength < input.length()) ? input[i + matchLength] : '\0';
                }
            }

            compressedData.push_back(make_tuple(longestMatchDistance, longestMatchLength, nextChar));
            i += longestMatchLength + 1; 
        }

        return compressedData;
    }
};


class LZ77Decompressor {
public:
    string decompress(const vector<tuple<int, int, char>> &compressedData) {
        string decompressedData;
        
        for (const auto &entry : compressedData) {
            int distance, length;
            char nextChar;
            tie(distance, length, nextChar) = entry;

            int start = decompressedData.length() - distance;
            for (int i = 0; i < length; ++i) {
                decompressedData.push_back(decompressedData[start + i]);
            }

            if (nextChar != '\0') {
                decompressedData.push_back(nextChar);
            }
        }

        return decompressedData;
    }
};

int main() {
    string input;
    cout << "Input sentence: ";
    getline(cin, input); 

    LZ77Compressor compressor;
    LZ77Decompressor decompressor;

    vector<tuple<int, int, char>> compressedData = compressor.compress(input);
    
    cout << "\nCompressed Data: \n";
    for (const auto &entry : compressedData) {
        int distance, length;
        char nextChar;
        tie(distance, length, nextChar) = entry;
        cout << "(" << distance << ", " << length << ", '" << nextChar << "') ";
    }
    cout << endl;

    string decompressedData = decompressor.decompress(compressedData);

    cout << "\nDecompresed Data: " << decompressedData << endl;

    return 0;
}
