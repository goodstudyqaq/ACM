#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {10, 6};
    int n[2] = {5, 6};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.smallestEvenMultiple(n[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}