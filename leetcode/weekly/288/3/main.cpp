#include "./solution.h"

int main() {
    Solution sol = Solution();
    long long res[1] = {3};
    vector<int> flowers[1] = {{1, 1}};
    long long t[1] = {2};
    int target[1] = {2};
    int full[1] = {1};
    int partial[1] = {2};
    for (int i = 0; i < 1; i++) {
        long long my_ans = sol.maximumBeauty(flowers[i], t[i], target[i], full[i], partial[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}