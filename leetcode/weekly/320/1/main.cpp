#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<vector<int>> res[2] = {{{2,2},{4,6},{15,-1}}, {{-1,4}}};
    TreeNode* root[2] = {new TreeNode({6,2,13,1,4,9,15,NULL,NULL,NULL,NULL,NULL,NULL,14}), new TreeNode({4,NULL,9})};
    vector<int> queries[2] = {{2,5,16}, {3}};
    for (int i = 0; i < 2; i++) {
        vector<vector<int>> my_ans = sol.closestNodes(root[i], queries[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}