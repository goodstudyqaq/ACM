#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {5, 0};
    vector<int> candies[2] = {{5, 8, 6}, {2, 5}};
    long long k[2] = {3, 11};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.maximumCandies(candies[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}