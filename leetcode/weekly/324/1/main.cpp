#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {5, 3};
    int n[2] = {15, 3};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.smallestValue(n[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}