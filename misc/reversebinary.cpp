// reversebinary.cpp
//
// spotify puzzle: reversebinary
//

#include <iostream>
using namespace std;

int main()
{
    int N; cin >> N;
    int rev = 0;
    while (N) {
        rev = (rev << 1) | (N & 1);
        N >>= 1;
    }
    cout << rev << endl;
}
