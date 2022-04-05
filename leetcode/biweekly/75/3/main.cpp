#include "./solution.h"

int main() {
    Solution sol = Solution();
    long long res[3] = {9, 14, 5};
    string s[3] = {"babab", "azbazbzaz", "wlkw"};
    for (int i = 0; i < 3; i++) {
        long long my_ans = sol.sumScores(s[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}