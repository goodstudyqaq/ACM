#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < int(n); i++)

int main() {
    cin.tie(0);
    iostream::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<string> s(3);
    forn(i, 3) cin >> s[i];
    vector<int> pr(n + 1);
    forn(i, n) {
        pr[i + 1] += pr[i];
        forn(j, 3) pr[i + 1] += (s[j][i] == '1');
    }

    vector<int> p(3 * n), rk(3 * n, 1);
    iota(p.begin(), p.end(), 0);
    function<int(int)> getp;
    getp = [&](int a) -> int {
        return a == p[a] ? a : p[a] = getp(p[a]);
    };
    auto unite = [&](int a, int b) -> bool {
        a = getp(a), b = getp(b);
        if (a == b) return false;
        if (rk[a] < rk[b]) swap(a, b);
        p[b] = a;
        rk[a] += rk[b];
        return true;
    };

    vector<int> prhe(n + 1), prve(n + 1);

    forn(j, n) {
        forn(i, 2) if (s[i][j] == '1' && s[i + 1][j] == '1' && unite(i * n + j, (i + 1) * n + j))++ prve[j + 1];
        forn(i, 3) if (j > 0 && s[i][j] == '1' && s[i][j - 1] == '1' && unite(i * n + j, i * n + (j - 1)))++ prhe[j];
    }
    forn(i, n) prve[i + 1] += prve[i];
    forn(i, n) prhe[i + 1] += prhe[i];

    vector<int> nxt(n + 1, 0);
    for (int i = n - 1; i >= 0; --i)
        nxt[i] = (s[0][i] == '1' && s[1][i] == '0' && s[2][i] == '1' ? (nxt[i + 1] + 1) : 0);

    int m;
    cin >> m;
    forn(_, m) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        int non101 = l + nxt[l];
        if (non101 > r) {
            cout << "2\n";
            continue;
        }
        int tot = pr[r + 1] - pr[non101];
        int in = (prve[r + 1] - prve[non101]) + (prhe[r] - prhe[non101]);
        int res = tot - in;
        if (non101 != l) {
            if (s[0][non101] == '1' && s[1][non101] == '1' && s[2][non101] == '1')
                ;
            else if (s[0][non101] == '0' && s[2][non101] == '0')
                res += 2;
            else
                ++res;
        }
        cout << res << "\n";
    }

    return 0;
}