#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<int> res[2] = {{2}, {3,2,3,2}};
    TreeNode* root[2] = {new TreeNode({1,3,4,2,NULL,6,5,NULL,NULL,NULL,NULL,NULL,7}), new TreeNode({5,8,9,2,1,3,7,4,6})};
    vector<int> queries[2] = {{4}, {3,2,4,8}};
    for (int i = 0; i < 2; i++) {
        vector<int> my_ans = sol.treeQueries(root[i], queries[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}