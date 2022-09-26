#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<string> res[2] = {{"Mary","Emma","John"}, {"Bob","Alice","Bob"}};
    vector<string> names[2] = {{"Mary","John","Emma"}, {"Alice","Bob","Bob"}};
    vector<int> heights[2] = {{180,165,170}, {155,185,150}};
    for (int i = 0; i < 2; i++) {
        vector<string> my_ans = sol.sortPeople(names[i], heights[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}