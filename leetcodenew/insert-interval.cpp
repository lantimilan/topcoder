/**
 * insert-interval.cpp
 * https://oj.leetcode.com/problems/insert-interval/
 *
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
        vector<Interval> ans;
        int i;
        for (i = 0; i < intervals.size(); ++i) {
            if (intervals[i].end < newInterval.start) ans.push_back(intervals[i]);
            else break;
        }
        // either overlap or newInterval is inserted before intervals[i]
        while (i < intervals.size() && overlap(newInterval, intervals[i])) {
            newInterval = extend(newInterval, intervals[i]);
            i++;
        }
        ans.push_back(newInterval);
        for (; i < intervals.size(); ++i) ans.push_back(intervals[i]);
        return ans;
    }

    bool overlap(Interval l1, Interval l2) {
        if (l1.end < l2.start) return false;
        if (l2.end < l1.start) return false;
        return true;
    }

    Interval extend(Interval l1, Interval l2) {
        int s = min(l1.start, l2.start);
        int e = max(l1.end, l2.end);
        return Interval(s, e);
    }
};
