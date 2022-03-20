#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<int> res[2] = {{0,0,0,0,1,1,0,0,1,2,3,1}, {0,0,0,0,0,0,0,0,1,1,1,0}};
    int numArrows[2] = {9, 3};
    vector<int> aliceArrows[2] = {{1,1,0,1,0,0,2,1,0,1,2,0}, {0,0,1,0,0,0,0,0,0,0,0,2}};
    for (int i = 0; i < 2; i++) {
        vector<int> my_ans = sol.maximumBobPoints(numArrows[i], aliceArrows[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}