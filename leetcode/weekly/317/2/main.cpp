#include "./solution.h"

int main() {
    Solution sol = Solution();
    long long res[3] = {4, 33, 0};
    long long it[3] = {16, 467, 1};
    int target[3] = {6, 6, 1};
    for (int i = 0; i < 3; i++) {
        long long my_ans = sol.makeIntegerBeautiful(it[i], target[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}