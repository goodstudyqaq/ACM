#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

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

    vector<int> work(string &s2) {
        int s1_sz = s.size();
        int m = s2.size();
        s += s2;
        int i = s1_sz, j = next[s1_sz];
        next.resize(s1_sz + m + 1);
        int M = s1_sz + m;
        vector<int> res;
        while (i < M) {
            while (j != -1 && s[i] != s[j]) j = next[j];
            next[++i] = ++j;
            res.push_back(j);
        }
        s.resize(s1_sz);
        next.resize(s1_sz + 1);
        return res;
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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    string s;
    cin >> s;
    KMP kmp(s);
    kmp.fast_kmp_pre();
    int q;
    cin >> q;
    while (q--) {
        string t;
        cin >> t;
        auto res = kmp.work(t);
        for (int i = 0; i < t.size(); i++) {
            cout << res[i] << ' ';
        }
        cout << endl;
    }
    return 0;
}