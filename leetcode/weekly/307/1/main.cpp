#include "./solution.h"

int main() {
    Solution sol = Solution();
    string res[2] = {"7449447", "9"};
    string num[2] = {"444947137", "00009"};
    for (int i = 0; i < 2; i++) {
        string my_ans = sol.largestPalindromic(num[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}