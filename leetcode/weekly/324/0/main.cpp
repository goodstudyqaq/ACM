#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[3] = {2, 3, 0};
    vector<string> words[3] = {{"aba","aabb","abcd","bac","aabc"}, {"aabb","ab","ba"}, {"nba","cba","dba"}};
    for (int i = 0; i < 3; i++) {
        int my_ans = sol.similarPairs(words[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}