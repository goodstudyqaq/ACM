#include "./solution.h"

int main() {
    Solution sol = Solution();
    long long res[2] = {4, 6};
    string text[2] = {"abdcdbc", "aabb"};
    string pattern[2] = {"ac", "ab"};
    for (int i = 0; i < 2; i++) {
        long long my_ans = sol.maximumSubsequenceCount(text[i], pattern[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}