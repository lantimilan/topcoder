// the-ultimate-question.cpp
#include <iostream>
using namespace std;

int main() {
    int a, b, c; cin >> a >> b >> c;
    int target = 42;
    if (a + b + c == target) {
        cout << a << '+' << b << '+' << c << endl;
    } else if (a + b * c == target) {
        cout << a << '+' << b << '*' << c << endl;
    } else if (a * b + c == target) {
        cout << a << '*' << b << '+' << c << endl;
    } else if (a * b * c == target) {
        cout << a << '*' << b << '*' << c << endl;
    } else {
        cout << "This is not the ultimate question" << endl;
    }
}
