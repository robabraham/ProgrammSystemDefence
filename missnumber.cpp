#include <iostream>

using namespace std;

class MissingNumberFinder {
private:
    int n;
public:
    MissingNumberFinder(int n) : n(n) {}

    int findMissingNumber(int arr[], int size) {
        int xorFull = 0;  
        int xorSubset = 0;  

        for (int i = 1; i <= n; ++i) {
            xorFull ^= i;
        }

        for (int i = 0; i < size; ++i) {
            xorSubset ^= arr[i];
        }

        return xorFull ^ xorSubset;
    }
};

int main() {
    int n;
    cout << "Enter the value of n: ";
    cin >> n;

    int size = n - 1;
    int* numbers = new int[size]; 

    cout << "Enter the elements of the array: " << endl;
    for (int i = 0; i < size; ++i) {
        cin >> numbers[i];
    }

    MissingNumberFinder finder(n);
    int missingNumber = finder.findMissingNumber(numbers, size);
    cout << "Missing number is: " << missingNumber << endl;

    delete[] numbers; 
    return 0;
}
