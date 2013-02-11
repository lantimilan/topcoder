// there is a O(n) time algorithm
//
// look at students[0], need = (K - s[0] % K) % K
// if students[1] can make up need, then do so
// this is always optimal because no move can keep floor[0] with same cost and
// make s[1] smaller.
// otherwise s[1] < need, then we can move s[0]%K up to floor[1]
// then if s[2] can make need, we are good
// else it is best to move s[2] down to floor[1], and we are optimal in floor[2]
// floor[3..n] is independent now
//
//
// compute the solution with min cost and min remainder for soln with same cost
//
// total = 0  // total is number of Jedi's needed
// extra = 0  // extra is combined students of floor-1 and floor
// for floor = 0 to n-1
//    need = (K - extra) % K  // if extra is 0, we want 0 here
//    x = students[i]
//    if (x >= need)
//      fill need
//      extra += need; x -= need;
//      total += extra / K; assert(extra % K == 0);
//      extra = x;
//    else
//      not enough to fill need, move extra to floor
//      extra += x; need -= x;
//      if can pull from floor+1, do this
//      more = min(need, students[i+1])
//      extra += more; total += ceil(extra / K); extra = 0
// deal with the (n-1)th floor here
// total += ceil(extra / K)
//
// Question: Why is this optimal?


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
