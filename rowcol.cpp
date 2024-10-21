#include <iostream>
#include <string>
using namespace std;

class Rowcol {
private:
    int numRows;
    int numCols;

public:
    Rowcol(int rows, int cols) : numRows(rows), numCols(cols) {}

    string encrypt(const string& message) {
        char matrix[100][100] = { ' ' };  

        int index = 0;
        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numCols; col++) {
                if (index < message.length()) {
                    matrix[row][col] = message[index++];
                } else {
                    matrix[row][col] = ' '; 
                }
            }
        }


        cout << "Matrix during encryption:\n";
        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numCols; col++) {
                cout << matrix[row][col] << ' ';
            }
            cout << endl;
        }

        
        string encrypted;
        for (int col = 0; col < numCols; col++) {
            for (int row = 0; row < numRows; row++) {
                encrypted += matrix[row][col];
            }
        }

        
        cout << "Encrypted matrix representation:\n";
        for (int col = 0; col < numCols; col++) {
            for (int row = 0; row < numRows; row++) {
                cout << matrix[row][col] << ' ';
            }
            cout << endl;
        }

        return encrypted;
    }

    string decrypt(const string& encryptedMessage) {
        char matrix[100][100] = { ' ' };  
        int index = 0;

        
        for (int col = 0; col < numCols; col++) {
            for (int row = 0; row < numRows; row++) {
                if (index < encryptedMessage.length()) {
                    matrix[row][col] = encryptedMessage[index++];
                } else {
                    matrix[row][col] = ' ';
                }
            }
        }
      
        string decrypted;
        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numCols; col++) {
                decrypted += matrix[row][col];
            }
        }

        return decrypted;
    }
};

int main() {
    string message;
    cout << "Enter a text: ";
    getline(cin, message);

    int numRows, numCols;
    cout << "Enter number of rows: ";
    cin >> numRows;
    cout << "Enter number of columns: ";
    cin >> numCols;

    Rowcol cipher(numRows, numCols);

    string encryptedMessage = cipher.encrypt(message);
    cout << "Encrypted message: " << encryptedMessage << endl;

    string decryptedMessage = cipher.decrypt(encryptedMessage);
    cout << "Decrypted message: " << decryptedMessage << endl;

    return 0;
}
