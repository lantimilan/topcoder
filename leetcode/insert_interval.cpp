/**
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
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int ss, ee;
        ss = newInterval.start;
        ee = newInterval.end;
        vector<Interval> ans;
        
        int i;        
        for (i=0; i<intervals.size(); ++i) {
            int s1, e1;
            s1 = intervals[i].start;
            e1 = intervals[i].end;
            if (e1 < ss) ans.push_back(intervals[i]);
            else if (s1 <= ee) {
                ss = min(ss, s1);
                ee = max(ee, e1);
            } else {
                break;
            }
        }
        ans.push_back(Interval(ss,ee));
        for (; i<intervals.size(); ++i) {
            ans.push_back(intervals[i]);
        }
        return ans;
    }
};