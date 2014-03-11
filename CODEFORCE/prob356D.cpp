// prob356D.cpp
//
// Solution:
// 1. first the max of all bags must be a top level bag, because no other bag
// can contain it
// 2. think about the simpliest case when the total number of coins, s, is
// equal to max, then it is easy to construct a solution which telescope
// all bags in decreasing order
// 3. now for the general case, if we have a top level collection of bags,
// other bags can be telescoped into the max bag and that is a complete
// solution
//
// the only case when there is no solution is that s < max, acutally not
// we have no solution when the knapsack problem has no solution
//
// now the problem becomes a knapsack problem with the desired solution
// must contain max
//
// this is one of the so-called aha problem, it is easy once you see it
//
// knapsack problem: can you do faster than O(n*s)?


#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int n, s;
int coins[70000+5];
bool used[70000+5];
bool knap[70000+5];
int pred[70000+5];
pair<int,int> input[70000+5];
pair<int, pair<int,int> > output[70000+5];
int contains[70000+5];
vector<int> bags;

int main()
{
    cin >> n >> s;
    for (int i = 0; i < n; ++i) {
        cin >> coins[i];
        input[i] = make_pair(coins[i], i);
    }
    sort(coins, coins + n);
    sort(input, input + n);

    // solve knapsack for s-max with coins[0..n-1)
    // when consider coins[i]
    // knap[t] is either already true from coins[0..i)
    // or knap[t-coins[i]] is true
    //
    // base case: knap[0] is true
    //
    // but knapsack is O(n^2) 70000 x 70000
    // too slow
    //
    // we need knap[s - max]
    int mx = coins[n-1];
    if (s < mx) {
        cout << -1 << endl;
        return 0;
    }
    knap[0] = true;
    for (int i = 0; i < n-1; ++i) {
        for (int t = s - mx; t > 0; --t) if (!knap[t]) {
            if (t - coins[i] >= 0 && knap[t - coins[i]]) {
                knap[t] = true;
                pred[t] = t - coins[i];
            }
        }
    }
    if (!knap[s - mx]) {
        cout << -1 << endl;
        return 0;
    }
    /*
    // mark all bags contain no other bags
    bags.clear();
    int val = s - mx;
    while (val) {
        int p = pred[val];
        bags.push_back(val - p);
        val = p;
    }
    for (int i = 0; i < bags.size(); ++i) {
        if (i) cout << ' ';
        cout << bags[i];
    } cout << endl;
    sort(bags.begin(), bags.end());
    int p1, p2;
    for (p1 = p2 = 0; p1 < n-1 && p2 < bags.size(); ++p1) {
        if (coins[p1] == bags[p2]) {
            used[p1] = true; p2++;
            contains[p1] = -1;
        }
    }
    int last = n-1;
    while (last >= 0) {
        int next;
        for (next = last - 1; next >= 0 && used[next]; --next) ;
        //cout << "last " << last << ' ' << next << endl;
        if (next < 0) break;
        contains[last] = next;
        last = next;
    }
    contains[last] = -1;
    for (int i = 0; i < n; ++i) {
        if (contains[i] < 0) {
            output[i] = make_pair(input[i].second,
                make_pair(input[i].first, -1));
        } else {
            int p = contains[i];
            int d = input[i].first - input[p].first;
            output[i] = make_pair(input[i].second,  // orig id
                make_pair(d, input[p].second));  // <coins, contained_id>
        }
    }
    sort(output, output + n);
    for (int i = 0; i < n; ++i) {
        if (output[i].second.second < 0) {
            cout << output[i].second.first << " 0" << endl;
        } else {
            cout << output[i].second.first << " 1 "
                << output[i].second.second + 1 << endl;
        }
    }
    */
}

// TLE, so O(n^2) is too slow for n = 70000
