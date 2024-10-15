#include <iostream>
using namespace std;

class MathOperations {
public:
    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
};

int main() {
    int num1, num2;
    MathOperations mathOps;

    cout << "Input numbers: ";
    cin >> num1 >> num2;

    int result = mathOps.gcd(num1, num2);

    cout << "Numbers GCD = " << result << endl;

    return 0;
}
