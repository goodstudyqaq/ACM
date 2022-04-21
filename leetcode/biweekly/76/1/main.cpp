#include "./solution.h"

int main() {
    Solution sol = Solution();
    long long res[2] = {9, 1};
    int total[2] = {20, 5};
    int cost1[2] = {10, 10};
    int cost2[2] = {5, 10};
    for (int i = 0; i < 2; i++) {
        long long my_ans = sol.waysToBuyPensPencils(total[i], cost1[i], cost2[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}