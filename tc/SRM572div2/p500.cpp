// check feasibility
// for two intervals opposite, if overlap, then dead
// suppose no two opposite intervals overlap, then they are independent
// we can work with two sets, one forward and one backward
// For same direction set, if one interval is fully contained in another, then dead
// if not, then there is a ways to do the transformation
// select the farthest one (closest to the goal) and move to the goal

#include <string>
using namespace std;

class NextOrPrev
{
public:

bool check(int a, int b, int c, int d)
{
    int a1, b1, c1, d1;  // careful, need to use min(a,b) and max(a,b)
    a1 = min(a,b); b1 = max(a,b);
    c1 = min(c,d); d1 = max(c,d);
    if ((a-b) * (c-d) <= 0) {
        // opposite direction
        if (c1 <= a1 && a1 <= d1) return false;
        if (c1 <= b1 && b1 <= d1) return false;
        if (a1 <= c1 && c1 <= b1) return false;
        if (a1 <= d1 && d1 <= b1) return false;
    } else {
        if (c1 <= a1 && a1 <= d1 && c1 <= b1 && b1 <= d1) return false;
        if (a1 <= c1 && c1 <= b1 && a1 <= d1 && d1 <= b1) return false;
    }
    return true;
}

// because no wrap around, there is only one way from transform one char to another char
int getMinimum(int nextCost, int prevCost, string start, string goal)
{
    int n = start.length();
    int cost = 0;
    for (int i = 0; i < n; ++i) {
        int cur;
        if (start[i] > goal[i]) cur = prevCost * (start[i] - goal[i]);
        else cur = nextCost * (goal[i] - start[i]);
        cost += cur;
    }
    // check impossible
    // if opposite directions, then cannot overlap
    // if same direction, cannot fully contain
    bool good = true;
    for (int i = 0; i < n; ++i)
    for (int j = i+1; j < n; ++j)
    {
        if (!check(start[i], goal[i], start[j], goal[j])) {
            good = false; goto done;
        }
    }
    done:
    if (good) return cost;
    else return -1;
}
};
