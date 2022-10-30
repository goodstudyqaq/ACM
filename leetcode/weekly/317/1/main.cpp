#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<vector<string>> res[2] = {{{"alice","one"},{"bob","two"}}, {{"alice","b"}}};
    vector<string> creators[2] = {{"alice","bob","alice","chris"}, {"alice","alice","alice"}};
    vector<string> ids[2] = {{"one","two","three","four"}, {"a","b","c"}};
    vector<int> views[2] = {{5,10,5,4}, {1,2,2}};
    for (int i = 0; i < 2; i++) {
        vector<vector<string>> my_ans = sol.mostPopularCreator(creators[i], ids[i], views[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}