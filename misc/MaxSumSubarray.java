// MaxSumSubarray.java
//
// Two algorithms:
// 1. O(n) time, O(1) space
// by discarding a prefix when it becomes strictly negative
// 2. O(n) time, O(n) space
// dp[n] = dp[n-1] + a[n-1]
// dp[i] is the best subarray sum ending at a[i-1]
// dp[0] = 0
//
// To run test, enable assertion (disabled by default)
//     java -ea MaxSumSubarray


public class MaxSumSubarray {
    public static int getMaxSum1(int[] a) {
        boolean allNegative = true;
        int maxElement = a[0];
        for (int i = 0; i < a.length; ++i) {
            if (a[i] >= 0) {
                allNegative = false;
            }
            maxElement = Math.max(maxElement, a[i]);
        }
        if (allNegative) {
            return maxElement;
        }
        int start, end;
        int maxSum = 0;  // we know some a[i] >= 0 at this point
        start = 0;
        while (start < a.length) {
            int curSum = 0;
            for (end = start; end < a.length; ++end) {
                curSum += a[end];
                if (curSum > maxSum) maxSum = curSum;
                if (curSum < 0) break;
            }
            start = end + 1;
        }
        return maxSum;
    }

    public static int getMaxSumDP(int[] a) {
        int[] dp = new int[a.length + 1];
        dp[0] = 0;
        for (int i = 0; i < a.length; ++i) {
            dp[i+1] = a[i];
            if (dp[i] >= 0) dp[i+1] += dp[i];
        }
        int ans = a[0];
        for (int i = 1; i <= a.length; ++i) {
            ans = Math.max(ans, dp[i]);
        }
        return ans;
    }

    public static void print(int[] a) {
        System.out.print("Print: ");
        for (int i = 0; i < a.length; ++i)
            System.out.print(a[i] + " ");
        System.out.println();
    }

    public static void main(String[] args) {
        int[][] a = new int[7][];
        a[0] = new int[]{1};
        a[1] = new int[]{1,-2};
        a[2] = new int[]{-1,-2};
        a[3] = new int[]{3, -1, -2};
        a[4] = new int[]{-1, 3, -1, -2};
        a[5] = new int[]{-1, -1, 3, -1, 2, -2};
        a[6] = new int[]{-1, -1, 3, -1, 2, -2, 3, 4, -1, 2};

        int[] b = new int[]{1, 1, -1, 3, 2, 4, 10};

        for (int i = 0; i < b.length; ++i) {
            print(a[i]);
            int s1 = getMaxSum1(a[i]);
            int s2 = getMaxSumDP(a[i]);
            System.out.println(s1);
            System.out.println(s2);
            assert s1 == s2 && s1 == b[i];
        }
    }
}

// Proof of getMaxSum1
// w.l.o.g we can view an optimal subarray as some subarray with a prefix
// attached. The algorithm guarantees that
// whenever the while loop terminates because curSum is negative,
// there can be no subarray of a[i..end] for every possible i = 0 to end-1
// in other words, there is no way to extend the current subarray to the left.
