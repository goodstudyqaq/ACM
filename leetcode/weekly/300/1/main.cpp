#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<vector<int>> res[2] = {{{3,0,2,6,8},{5,0,-1,-1,1},{5,2,4,9,7}}, {{0,1,2,-1}}};
    int m[2] = {3, 1};
    int n[2] = {5, 4};
    ListNode* head[2] = {new ListNode({3,0,2,6,8,1,7,9,4,2,5,5,0}), new ListNode({0,1,2})};
    for (int i = 0; i < 2; i++) {
        vector<vector<int>> my_ans = sol.spiralMatrix(m[i], n[i], head[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}