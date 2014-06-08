/**
 * merge-intervals.cpp
 * https://oj.leetcode.com/problems/merge-intervals/
 *
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

bool compare(const Interval &l1, const Interval &l2) {
    if (l1.start != l2.start) return l1.start < l2.start;
    if (l1.end != l2.end) return l1.end < l2.end;
    return false;
}
class Solution {
public:
    vector<Interval> merge(vector<Interval> &intervals) {
        if (intervals.empty()) return vector<Interval>();
        sort(intervals.begin(), intervals.end(), compare);
        vector<Interval> mergedInterval; mergedInterval.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); ++i) {
            Interval last = mergedInterval.back();
            if (overlap(last, intervals[i])) {
                last = extend(last, intervals[i]);
                mergedInterval.pop_back(); mergedInterval.push_back(last);
            } else {
                mergedInterval.push_back(intervals[i]);
            }
        }
        return mergedInterval;
    }

    bool overlap(Interval l1, Interval l2) {
        return l1.end >= l2.start;
    }
    Interval extend(Interval l1, Interval l2) {
        int s = min(l1.start, l2.start);
        int e = max(l1.end, l2.end);
        return Interval(s, e);
    }
};
