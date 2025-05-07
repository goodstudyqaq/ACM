#include <bits/stdc++.h>

#include <algorithm>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

/*
真前缀：除了 S 本身的 S 的前缀
真后缀：除了 S 本身的 S 的后缀
https://oi-wiki.org/string/basic/
前缀函数 pi[i] = 子串 s[0...i] 最长的相等的真前缀与真后缀的长度
pi[0] = 0
*/

/*
KMP 的本质是 next 数组，next[i] 表示子串 s[0:i] 最长的相等的真前缀与真后缀的长度
*/
struct KMP {
    string s;
    vector<int> next;
    KMP(const string &_s) {
        s = _s;
        kmp_pre();
    }

    void kmp_pre() {
        int m = s.size();
        next.resize(m + 1);
        next[0] = -1;
        for (int i = 1; i <= m; i++) {
            int j = next[i - 1];
            while (j != -1 && s[i - 1] != s[j]) j = next[j];
            next[i] = j + 1;
        }
    }

    void fast_kmp_pre() {
        // 想想什么时候需要用到 next[i], 进行匹配时，到 s[i] 时失配，那么这时我们需要跳到 next[i].
        int m = s.size();
        next.resize(m + 1);
        int j = -1;
        next[0] = -1;
        for (int i = 1; i <= m; i++) {
            while (j != -1 && s[i - 1] != s[j]) j = next[j];
            j++;
            if (i < m && s[i] == s[j]) {
                next[i] = next[j];
            } else {
                next[i] = j;
            }
        }
    }

    // 计算 s 在 t 中出现的位置
    vector<int> count(const string &t) {
        int m = s.size();
        int n = t.size();
        vector<int> ans;
        int now = 0;
        for (int i = 0; i < n; i++) {
            while (now != -1 && t[i] != s[now]) {
                now = next[now];
            }
            now++;
            // t[0:i+1] 的后缀和 s 的前缀的最长相等长度为 now
            if (now == m) {
                ans.push_back(i - m + 1);
            }
        }
        return ans;
    }

    // 最小循环节
    // 返回最小循环节以及循环次数
    // 如果没有循环节，那么返回原串 和 1
    pair<string, int> calc_min_period() {
        int n = s.size();
        int m = next[n];
        if (m > 0 && n % (n - m) == 0) {
            return {s.substr(0, n - m), n / (n - m)};
        } else {
            return {s, 1};
        }
    }

    // 统计 s 的每个前缀出现的次数
    // ans[i] 表示长度为 i 的前缀出现的次数
    // https://oi-wiki.org/string/kmp/#%E7%BB%9F%E8%AE%A1%E6%AF%8F%E4%B8%AA%E5%89%8D%E7%BC%80%E7%9A%84%E5%87%BA%E7%8E%B0%E6%AC%A1%E6%95%B0
    // todo: 待验证
    vector<int> calc_prefix_number() {
        int n = s.size();
        vector<int> ans(n + 1, 1);  // 自身

        for (int i = 1; i <= n; i++) {
            ans[next[i]]++;
        }

        for (int i = n; i > 0; i--) {
            ans[next[i]] += ans[i];
        }
        return ans;
    }

    // 统计 s 的每个前缀在 t 中出现的次数
    // todo: 待验证
    vector<int> calc_prefix_number(const string &t) {
        int m = s.size();
        int n = t.size();

        vector<int> ans(m + 1);

        int now = 0;
        for (int i = 0; i < n; i++) {
            while (now != -1 && t[i] != s[now]) {
                now = next[now];
            }
            now++;
            ans[now]++;
        }

        for (int i = n; i > 0; i--) {
            ans[next[i]] += ans[i];
        }
        return ans;
    }
};

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    string s;
    cin >> s;
    KMP kmp(s);

    auto &next = kmp.next;

    int n = s.size();
    vector<int> cnt(n + 1);
    for (int i = 1; i <= n; i++) {
        int val = next[i];
        cnt[val]++;
    }
    debug(cnt);

    for (int i = n; i >= 1; i--) {
        int go = next[i];
        debug(i, go);
        cnt[go] += cnt[i];
    }
    for (int i = 1; i <= n; i++) {
        cnt[i]++;
    }

    debug(cnt);

    vector<pair<int, int>> ans;

    int now = next[n];

    while (now > 0) {
        ans.push_back({now, cnt[now]});
        now = next[now];
    }

    cout << ans.size() + 1 << '\n';
    reverse(ans.begin(), ans.end());
    for (auto it : ans) {
        cout << it.first << ' ' << it.second << '\n';
    }
    cout << n << ' ' << 1 << '\n';
}