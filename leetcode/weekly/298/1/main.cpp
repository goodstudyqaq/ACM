#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[3] = {2, -1, 0};
    int num[3] = {58, 37, 0};
    int k[3] = {9, 2, 7};
    for (int i = 0; i < 3; i++) {
        int my_ans = sol.minimumNumbers(num[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}