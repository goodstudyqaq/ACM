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
        // cin.tie(nullptr);
        // ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

int n;
int ask(string &s) {
    cout << s << endl;
    fflush(stdout);
    int res;
    cin >> res;
    if (res == n || res == -1) {
        exit(0);
    }
    fflush(stdout);
    return res;
}

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif
    cin >> n;
    string TTT(n, 'T');
    string TFT(n, 'T');

    for (int i = 1; i < n; i += 2) {
        TFT[i] = 'F';
    }
    int T_num = ask(TTT);
    int TF_num = ask(TFT);

    int l = 0, r = n - 1;

    string ans(n, '?');
    while (l <= r) {
        if (l == r) {
            string s = TTT;
            s[l] = 'F';
            int res = ask(s) - T_num;
            if (res == 1) {
                ans[l] = 'F';
            } else {
                ans[l] = 'T';
            }
            break;
        } else if (r == l + 1) {
            string s = TTT;
            s[l] = s[l + 1] = 'F';
            int res = ask(s) - T_num;
            if (res == 2) {
                ans[l] = ans[l + 1] = 'F';
            } else if (res == -2) {
                ans[l] = ans[l + 1] = 'T';
            } else {
                s = TFT;
                s[l] = 'F', s[l + 1] = 'T';
                res = ask(s) - TF_num;
                if (res == 2) {
                    ans[l] = 'F', ans[l + 1] = 'T';
                } else {
                    ans[l] = 'T', ans[l + 1] = 'F';
                }
            }
            break;
        } else {
            string s = TTT;
            s[l] = s[l + 1] = 'F';
            int res = ask(s) - T_num;
            if (res == 2) {
                ans[l] = ans[l + 1] = 'F';
                l += 2;
            } else if (res == -2) {
                ans[l] = ans[l + 1] = 'T';
                l += 2;
            } else {
                s = TFT;
                s[l] = 'F', s[l + 1] = 'T';
                if (TFT[r] == 'T')
                    s[r] = 'F';
                else
                    s[r] = 'T';
                res = ask(s) - TF_num;

                if (res == 3) {
                    ans[l] = 'F', ans[l + 1] = 'T';
                    ans[r] = s[r];
                } else if (res == -3) {
                    ans[l] = 'T', ans[l + 1] = 'F';
                    ans[r] = TFT[r];
                } else if (res == 1) {
                    ans[l] = 'F', ans[l + 1] = 'T';
                    ans[r] = TFT[r];
                } else {
                    ans[l] = 'T', ans[l + 1] = 'F';
                    ans[r] = s[r];
                }
                l += 2;
                r--;
            }
        }
    }
    ask(ans);
}