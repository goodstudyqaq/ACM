#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[3] = {1, 1, -1};
    vector<string> words[3] = {{"hello","i","am","leetcode","hello"}, {"a","b","leetcode"}, {"i","eat","leetcode"}};
    string target[3] = {"hello", "leetcode", "ate"};
    int startIndex[3] = {1, 0, 0};
    for (int i = 0; i < 3; i++) {
        int my_ans = sol.closetTarget(words[i], target[i], startIndex[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}