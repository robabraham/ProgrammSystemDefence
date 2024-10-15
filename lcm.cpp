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

    
    int lcm(int a, int b) {
        return (a * b) / gcd(a, b);
    }
};

int main() {
    int num1, num2;
    MathOperations mathOps;

    cout << "Input numbers: ";
    cin >> num1 >> num2;

    int result = mathOps.lcm(num1, num2);

    cout << "Numbers LCM = " << result << endl;

    return 0;
}
