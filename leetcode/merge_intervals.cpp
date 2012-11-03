/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
 
class Compare {
public:
    bool operator()(const Interval &v1, const Interval &v2) {
        if (v1.start != v2.start) return v1.start < v2.start;
        return v1.end < v2.end;
    }
};
class Solution {
public:
    bool overlap(const Interval &v1, const Interval &v2) {
        if (v1.start <= v2.end && v1.end >= v2.start)
            return true;
        return false;
    }
    vector<Interval> merge(vector<Interval> &intervals) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (intervals.empty()) return intervals;
        
        sort(intervals.begin(), intervals.end(), Compare());
        vector<Interval> ans;
        Interval curr = intervals[0];
        for (int i=1; i<intervals.size(); ++i) {
            if (overlap(curr, intervals[i])) {
                curr.start = min(curr.start, intervals[i].start);
                curr.end = max(curr.end, intervals[i].end);
            } else {
                ans.push_back(curr);
                curr = intervals[i];
            }
        }
        ans.push_back(curr);
        return ans;
    }
};
