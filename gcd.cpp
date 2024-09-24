Բաժանարար 
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

int main() {
    int num1, num2; 

    cout << "Մուտքագրեք երկու ամբողջ թիվ: ";
    cin >> num1 >> num2; 

    int result = gcd(num1, num2); 

    cout << "Երկու թվերի ամենամեծ ընդհանուր բաժանարարը = " << result << endl; 

    return 0;
}
