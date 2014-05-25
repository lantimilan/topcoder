/**
* gas-station.cpp
* https://oj.leetcode.com/problems/gas-station/
*/
class Solution {
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
        // start at any station, keep going while amount >= 0
        // stop if amount < 0
        // then start fresh from next station
        vector<bool> visit(gas.size());
        int station = 0;
        while (!visit[station]) {
            int amount = 0;
            int cur = station;
            while (true) {
                visit[cur] = true;
                amount += gas[cur];
                amount -= cost[cur];
                if (amount < 0) break;
                cur = advance(cur, gas.size());  // we have reached cur
                if (cur == station) return station;
            }
            // fail to reach cur+1 because run out of gas, restart from cur+1
            station = advance(cur, gas.size());
        }
        return -1;
    }
    int advance(int pos, int n) {
        int next = pos + 1;
        if (next >= n) next = 0;
        return next;
    }
};
