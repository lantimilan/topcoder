#include <iomanip>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int main()
{
    vector<double> vec;
    double d;
    while (cin >> d) {
        //cout << fixed << setprecision(5) << sqrt(d) << endl;
        vec.push_back(sqrt(d));
    }
    for (int i=vec.size()-1; i>=0; --i)
        cout << fixed << setprecision(5) << vec[i] << endl;

}
