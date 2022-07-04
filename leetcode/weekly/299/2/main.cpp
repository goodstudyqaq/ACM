#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[3] = {210, 220, 31};
    vector<int> nums1[3] = {{60,60,60}, {20,40,20,70,30}, {7,11,13}};
    vector<int> nums2[3] = {{10,90,10}, {50,20,50,40,20}, {1,1,1}};
    for (int i = 0; i < 3; i++) {
        int my_ans = sol.maximumsSplicedArray(nums1[i], nums2[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}