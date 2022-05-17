#include <bits/stdc++.h>
using namespace std;
struct Manacher {
    string s;
    vector<int> Mp;
    Manacher(string &_s) {
        s = "";
        int n = _s.size();
        s += "$";
        s += "#";
        for (int i = 0; i < n; i++) {
            s += _s[i];
            s += "#";
        }
        s += "?";
        int id = 0, mx = 0;
        int l = s.size();
        Mp.resize(l);
        for (int i = 0; i < l - 1; i++) {
            Mp[i] = mx > i ? min(Mp[2 * id - i], mx - i) : 1;
            while (i + Mp[i] < l && i - Mp[i] >= 0 && s[i + Mp[i]] == s[i - Mp[i]]) Mp[i]++;
            if (i + Mp[i] > mx) {
                mx = i + Mp[i];
                id = i;
            }
        }
    }
    Manacher() {}

    int query(int l, int r) {
        // l = r 那么就表示以 l 为中心的最长回文串
        // l + 1 = r 那么就表示以 l 和 r 中间为中心的最长回文串
        // 返回长度
        int idx = (l + 1) * 2;
        if (l != r) {
            idx++;
        }
        int length = Mp[idx];
        return length / 2;
    }
};