#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {3, 3};
    int start[2] = {10, 3};
    int goal[2] = {7, 4};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.minBitFlips(start[i], goal[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}