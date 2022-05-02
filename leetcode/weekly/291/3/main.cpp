#include "./solution.h"

int main() {
    Solution sol = Solution();
    long long res[2] = {28, 20};
    string s[2] = {"abbca", "code"};
    for (int i = 0; i < 2; i++) {
        long long my_ans = sol.appealSum(s[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}