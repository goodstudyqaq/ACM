#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;

template < typename A, typename B >
string to_string(pair< A, B > p);

template < typename A, typename B, typename C >
string to_string(tuple< A, B, C > p);

template < typename A, typename B, typename C, typename D >
string to_string(tuple< A, B, C, D > p);

string to_string(const string& s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string)s);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

string to_string(vector< bool > v) {
    bool first = true;
    string res = "{";
    for (int i = 0; i < static_cast< int >(v.size()); i++) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(v[i]);
    }
    res += "}";
    return res;
}

template < size_t N >
string to_string(bitset< N > v) {
    string res = "";
    for (size_t i = 0; i < N; i++) {
        res += static_cast< char >('0' + v[i]);
    }
    return res;
}

template < typename A >
string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto& x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

template < typename A, typename B >
string to_string(pair< A, B > p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template < typename A, typename B, typename C >
string to_string(tuple< A, B, C > p) {
    return "(" + to_string(get< 0 >(p)) + ", " + to_string(get< 1 >(p)) + ", " + to_string(get< 2 >(p)) + ")";
}

template < typename A, typename B, typename C, typename D >
string to_string(tuple< A, B, C, D > p) {
    return "(" + to_string(get< 0 >(p)) + ", " + to_string(get< 1 >(p)) + ", " + to_string(get< 2 >(p)) + ", " + to_string(get< 3 >(p)) + ")";
}

void debug_out() {
    cerr << endl;
}

template < typename Head, typename... Tail >
void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

vector< int > a;
vector< int > x;
int xcnt;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    freopen("data.in", "r", stdin);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        a.resize(n + 1);
        x.resize(n);
        xcnt = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            x[xcnt++] = a[i];
        }
        sort(x.begin(), x.begin() + xcnt);
        xcnt = unique(x.begin(), x.end()) - x.begin();

        vector< int > cnt(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            a[i] = lower_bound(x.begin(), x.begin() + xcnt, a[i]) - x.begin() + 1;
            cnt[a[i]]++;
        }
        // debug(a);

        vector< int > dp(n + 1, 0);
        // dp[i] 表示到 i 位置的最长连续序列的长度
        /*
		如果前面有 a[i], 那么 dp[i] = max(dp[i], dp[last[a[i]]] + 1)
		如果 a[i] - 1 前面出现完毕 dp[i] = max(dp[i], dp[first[a[i] - 1]] + 1)
		如果 a[i] - 1 没有出现完毕 dp[i] = max(dp[i], now_cnt[a[i] - 1] + 1)
		*/
        vector< int > first(n + 1, -1);
        vector< int > now_cnt(n + 1, 0);
        vector< int > last(n + 1, -1);
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            int val = a[i];
            dp[i] = 1;
            if (last[val] != -1) {
                dp[i] = max(dp[i], dp[last[val]] + 1);
            }
            int val2 = a[i] - 1;
            if (val2 != 0) {
                if (now_cnt[val2] == cnt[val2]) {
                    dp[i] = max(dp[i], dp[first[val2]] + cnt[val2]);
                } else {
                    dp[i] = max(dp[i], now_cnt[val2] + 1);
                }
            }
            if (first[val] == -1) {
                first[val] = i;
            }
            now_cnt[val]++;
            last[val] = i;
            // debug(i, dp[i]);
            ans = max(ans, dp[i]);
        }
        cout << n - ans << '\n';
    }
    return 0;
}