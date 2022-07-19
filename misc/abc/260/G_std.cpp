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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    vector<vector<int>> sum1 = vector(n, vector(2 * m + n, 0));
    vector<vector<int>> sum2 = vector(n, vector(2 * m + n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (s[i][j] == 'O') {
                sum1[i][j]++;
                if (i + m < n) {
                    sum1[i + m][j]--;
                }
                sum2[i][2 * m + j]--;
                if (i + m < n && j >= 0) {
                    sum2[i + m][j]++;
                }
            }
        }
    }

    vector sum3 = vector(n, vector(2 * m + n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2 * m + n; j++) {
            if (i) {
                sum1[i][j] += sum1[i - 1][j];
            }

            if (i && j + 2 < 2 * m + n) {
                sum2[i][j] += sum2[i - 1][j + 2];
            }

            sum3[i][j] = sum1[i][j] + sum2[i][j];
            if (j)
                sum3[i][j] += sum3[i][j - 1];
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        cout << sum3[x - 1][y - 1] << endl;
    }
    return 0;
}