// got a bit scared as I thought 0^0 is 1, then case 1 is wrong
//
// I had the right idea but was not careful in implementation
//
// each pos works by itself
//
// 011 requires zero
// 000001 requires one
// 000000 requires two
// 111111 requires one
//
#include <string>
#include <vector>
using namespace std;

class TheDevice
{
public:

int minimumAdditional(vector <string> plates)
{
    int len = plates[0].size();
    int ans = 0;
    for (int i=0; i<len; ++i)
    {
        int curr;
        int b[2] = {0};
        for (int k=0; k<plates.size(); ++k) {
            b[0] += plates[k][i] == '0';
            b[1] += plates[k][i] == '1';
        }
        if (b[0]>=1) {
            if (b[1] >= 2) curr = 0;
            else if (b[1] == 1) curr = 1;
            else curr = 2;
        } else {
            if (b[1] >= 2) curr = 1;
            else curr = 2;
        }
        ans = max(ans, curr);
    }
    return ans;
}
};
