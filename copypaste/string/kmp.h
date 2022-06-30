#include <bits/stdc++.h>
using namespace std;

/*
KMP 的本质是 next 数组，即找到以当前 i 结尾的 s 子串与前缀完全等价的最长后缀的长度。
注意这里没有用相同，而是用完全等价这个词，根据不同题意，完全等价的意义是不同的，但核心是最终变出来的东西是一模一样的。
但感觉好像只能是相等啊？？？？
*/
struct KMP {
    string s;
    vector<int> next;  // next[i] 表示前缀长度为 i 的子串 s 的与前缀相同的最长后缀的长度
    KMP(string &_s) {
        s = _s;
    }

    void kmp_pre() {
        int m = s.size();
        next.resize(m + 1);
        int i, j;
        j = next[0] = -1;
        i = 0;
        while (i < m) {
            while (j != -1 && s[i] != s[j]) j = next[j];
            next[++i] = ++j;
        }
    }

    void fast_kmp_pre() {
        int m = s.size();
        next.resize(m + 1);
        int i, j;
        j = next[0] = -1;
        i = 0;
        while (i < m) {
            while (j != -1 && s[i] != s[j]) j = next[j];
            if (s[++i] == s[++j])
                next[i] = next[j];
            else
                next[i] = j;
        }
    }

    // 计算 s 在 s2 中出现的次数, 需要先调用 kmp_pre 函数
    int count(string s2) {
        int m = s.size();
        int n = s2.size();
        int i = 0, j = 0;
        int ans = 0;
        while (i < n) {
            while (j != -1 && s2[i] != s[j]) {
                j = next[j];
            }
            i++, j++;
            if (j >= m) {
                ans++;
            }
        }
        return ans;
    }
};