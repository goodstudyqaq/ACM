#include "./solution.h"

int main() {
    Solution sol = Solution();
    long long res[3] = {2, 1, 0};
    vector<int> nums[3] = {{8,12,6}, {1,2,5}, {1,1,1,1,1}};
    vector<int> target[3] = {{2,14,10}, {4,1,3}, {1,1,1,1,1}};
    for (int i = 0; i < 3; i++) {
        long long my_ans = sol.makeSimilar(nums[i], target[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}