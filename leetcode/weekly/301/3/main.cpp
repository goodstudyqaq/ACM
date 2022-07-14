#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {10, 11};
    int n[2] = {2, 5};
    int maxValue[2] = {5, 3};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.idealArrays(n[i], maxValue[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}