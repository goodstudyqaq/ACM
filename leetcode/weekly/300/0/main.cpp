#include "./solution.h"

int main() {
    Solution sol = Solution();
    string res[2] = {"this is a secret", "the five boxing wizards jump quickly"};
    string key[2] = {"the quick brown fox jumps over the lazy dog", "eljuxhpwnyrdgtqkviszcfmabo"};
    string message[2] = {"vkbs bs t suepuv", "zwx hnfx lqantp mnoeius ycgk vcnjrdb"};
    for (int i = 0; i < 2; i++) {
        string my_ans = sol.decodeMessage(key[i], message[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}