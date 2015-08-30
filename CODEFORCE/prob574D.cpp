// prob574D.cpp
#include <iostream>
using namespace std;

int h[100000+5];
int myleft[100000+5];
int myright[100000+5];

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> h[i];

    myleft[0] = 1;
    for (int i = 1; i < n; ++i) {
        myleft[i] = min(h[i], myleft[i-1] + 1);
    }
    myright[n-1] = 1;
    for (int i = n-2; i >= 0; --i) {
        myright[i] = min(h[i], myright[i+1] + 1);
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, min(myleft[i], myright[i]));
    }
    cout << ans << endl;
}
