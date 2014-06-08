/**
* valid-number.cpp
* https://oj.leetcode.com/problems/valid-number/
*
*/
class Solution {
public:
    bool isNumber(const char *s) {
        const char *start, *end, *p;
        for (start = s; *start && *start == ' '; ++start) ;
        if (!*start) return false;
        for (end = start + 1; *end && *end != ' '; ++end) ;
        // [start..end) marks the first space delimited token
        for (p = end; *p; ++p) if (*p != ' ') return false;  // xxx xx xxx
        // now [start, end) is a token
        // integer
        // check int
        bool isInt = checkInt(start, end);
        if (isInt) return true;
        // check floating point
        bool isFP = checkFP(start, end);
        if (isFP) return true;
        // check scientific
        bool isSci = true;
        const char *expo;
        for (expo = start; expo < end; ++expo) {
            if (*expo == 'e' || *expo == 'E') break;
        }
        if (expo >= end) isSci = false;
        else isSci = (checkInt(start, expo) || checkFP(start, expo)) && checkInt(expo+1, end);
        return isSci;
    }

    bool checkInt(const char *start, const char *end) {
        if (*start == '+' || *start == '-') start++;
        if (start == end) return false;  // empty
        //if (start + 1 < end && *start == '0') return false;  // leading zero
        for (const char *p = start; p < end; ++p)
            if (!isdigit(*p))
                return false;
        return true;
    }

    bool checkFP(const char *start, const char *end) {
        if (*start == '+' || *start == '-') start++;
        const char *pt, *p;
        for (pt = start; pt < end && *pt != '.'; ++pt) ;
        if (pt >= end) return false;  // no decimal point
        else {
            if (start >= pt && pt + 1 >= end) return false;  // both segment around decimal point empty
            //if (pt - start > 1 && *start == '0') return false;  // leading zero before decimal point
            for (p = start; p < pt; ++p) if (!isdigit(*p)) return false;
            for (p = pt+1; p < end; ++p) if (!isdigit(*p)) return false;
        }
        return true;
    }
};
