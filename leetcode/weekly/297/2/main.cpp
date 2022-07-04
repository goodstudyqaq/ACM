#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {31, 7};
    vector<int> cookies[2] = {{8,15,10,20,8}, {6,1,3,2,2,4,1,2}};
    int k[2] = {2, 3};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.distributeCookies(cookies[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}