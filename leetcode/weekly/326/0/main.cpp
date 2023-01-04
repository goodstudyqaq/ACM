#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[3] = {1, 2, 4};
    int num[3] = {7, 121, 1248};
    for (int i = 0; i < 3; i++) {
        int my_ans = sol.countDigits(num[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}