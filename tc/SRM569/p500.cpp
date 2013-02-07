// try all possible centers to redistribute
//
// my problem is I did not realize you do not have
// to redistribute everything to centers
//
// nonetheless this is my first submission to div1 500
// also very close to the real solution
//
#include <algorithm>
#include <vector>
using namespace std;

class TheJediTest
{
public:

int minimumSupervisors(vector <int> students, int K)
{
    int ans = -1;
    int N = students.size();
    for (int mask = 0; mask < (1<<N); ++mask)
    {
        vector<int> vec = students;
        for (int i=0; i<N; ++i)
        {
            if (mask & 1<<i) { // center
                int rem = vec[i] % K;
                int need = K - rem;
                if (i+1 < N) {  // fill from above
                    int transfer = min(need, students[i+1]);  // can only get students[i+1]
                    vec[i] += transfer; vec[i+1] -= transfer;
                }
            } else {  // transfer all students from i to i+1 if possible
                if (i+1 < N && (mask & 1<<i+1)) {
                    vec[i+1] += vec[i]; vec[i] = 0;
                }
            }
        }
        int curr = 0;
        for (int i=0; i<N; ++i) {
            curr += (vec[i]+K-1)/K;
        }
        if (ans < 0 || ans > curr) ans = curr;
    }
    return ans;
}
};
