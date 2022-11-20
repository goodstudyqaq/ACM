#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[3] = {3, 1, 1};
    string s[3] = {"23542185131", "23542185131", "3312958"};
    int k[3] = {3, 3, 3};
    int minLength[3] = {2, 3, 1};
    for (int i = 0; i < 3; i++) {
        int my_ans = sol.beautifulPartitions(s[i], k[i], minLength[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}