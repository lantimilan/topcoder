// test.cpp
#include <iostream>
using namespace std;

template<int val>
void print() {
    cout << val << endl;
}

int main()
{
    print<1>();
    print<2>();
    int a=1;
    print<a>();  // This will not compile.
}
