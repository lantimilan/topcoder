// start from previous height, keep moving up until fit
//
// box width <= n and stairs have width 1 to n for stair[0] to stair[n-1]
//

#include <algorithm>
#include <cassert>
#include <iostream>
using namespace std;

int height[100000+5];
int width[100000+5];

int main()
{
    int n, m;
    cin >> n;
    for (int i=0; i<n; ++i) { cin >> height[i]; }
    for (int i=0; i<n; ++i) width[i] = i+1;

    long long start = height[0], box = 0;
    cin >> m;
    for (int i=0; i<m; ++i) {
        int w, h;
        long long land;
        cin >> w >> h;

        //cout << w << ' ' << h << ' ' << start << ' ' << box << endl;
            for (; box < n && width[box] < w; ++box) ;
            assert(box < n);
            //for (; box+1 < n && height[box+1] <= start; ++box) ;
            land = max(start, (long long)height[box]);
            start = land + h;
        cout << land << endl;
    }
}

// Accepted
