#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {4, -1};
    string s[2] = {"165462", "238182"};
    int k[2] = {60, 5};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.minimumPartition(s[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}