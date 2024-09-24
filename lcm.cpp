Բազմապատիկ 

#include <iostream>
using namespace std;


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

int main() {
    int num1, num2; 

    cout << "Մուտքագրեք երկու ամբողջ թիվ: ";
    cin >> num1 >> num2; 

    int result = lcm(num1, num2); 

    cout << "Երկու թվերի ամենափոքր ընդհանուր բազմապատիկը = " << result << endl; 

    return 0;
}
