#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<int> res[2] = {{5,4,3,2}, {4}};
    vector<string> words[2] = {{"abc","ab","bc","b"}, {"abcd"}};
    for (int i = 0; i < 2; i++) {
        vector<int> my_ans = sol.sumPrefixScores(words[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}