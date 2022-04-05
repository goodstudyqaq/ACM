#include "./solution.h"

int main() {
    Solution sol = Solution();
    long long res[2] = {6, 0};
    string s[2] = {"001101", "11100"};
    for (int i = 0; i < 2; i++) {
        long long my_ans = sol.numberOfWays(s[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}