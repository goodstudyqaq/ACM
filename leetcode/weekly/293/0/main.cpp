#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<string> res[2] = {{"abba","cd"}, {"a","b","c","d","e"}};
    vector<string> words[2] = {{"abba","baba","bbaa","cd","cd"}, {"a","b","c","d","e"}};
    for (int i = 0; i < 2; i++) {
        vector<string> my_ans = sol.removeAnagrams(words[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}