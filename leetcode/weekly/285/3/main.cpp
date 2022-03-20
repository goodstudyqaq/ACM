#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<int> res[1] = {{1,1,1,1,1,1,1,1}};
    string s[1] = {"mm"};
    string queryCharacters[1] = {"bfviuwsr"};
    vector<int> queryIndices[1] = {{0,0,1,0,0,1,1,0}};
    for (int i = 0; i < 1; i++) {
        vector<int> my_ans = sol.longestRepeating(s[i], queryCharacters[i], queryIndices[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}