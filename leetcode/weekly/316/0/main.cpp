#include "./solution.h"

int main() {
    Solution sol = Solution();
    bool res[3] = {true, true, false};
    vector<string> event1[3] = {{"01:15","02:00"}, {"01:00","02:00"}, {"10:00","11:00"}};
    vector<string> event2[3] = {{"02:00","03:00"}, {"01:20","03:00"}, {"14:00","15:00"}};
    for (int i = 0; i < 3; i++) {
        bool my_ans = sol.haveConflict(event1[i], event2[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}