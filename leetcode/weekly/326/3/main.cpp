#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<int> res[2] = {{11,13}, {-1,-1}};
    int left[2] = {10, 4};
    int right[2] = {19, 6};
    for (int i = 0; i < 2; i++) {
        vector<int> my_ans = sol.closestPrimes(left[i], right[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}