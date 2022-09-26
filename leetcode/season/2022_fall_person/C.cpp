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

const int maxn = 1005;
int dis[maxn][maxn][4];
int d[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
typedef array<int, 3> a3;
a3 my_queue[maxn * maxn * 4];
int qcnt = 0;
const int inf = 1e9;
// class Solution {
//    public:
//     vector<vector<int>> ballGame(int num, vector<string>& s) {
//         qcnt = 0;
//         int n = s.size();
//         int m = s[0].size();
//         for (int i = 0; i < n; i++) {
//             for (int j = 0; j < m; j++) {
//                 for (int k = 0; k < 4; k++) {
//                     dis[i][j][k] = inf;
//                 }
//             }
//         }
//         for (int i = 0; i < n; i++) {
//             for (int j = 0; j < m; j++) {
//                 if (s[i][j] == 'O') {
//                     for (int k = 0; k < 4; k++) {
//                         my_queue[qcnt++] = {i, j, k};
//                         dis[i][j][k] = 0;
//                     }
//                 }
//             }
//         }
//         vector<vector<int>> ans;
//         int now = 0;
//         while (now < qcnt) {
//             auto [x, y, dir] = my_queue[now];
//             debug(x, y, dir, dis[x][y][dir]);
//             now++;
//             if (dis[x][y][dir] > num) continue;
//             int x2 = x + d[dir][0], y2 = y + d[dir][1];
//             if (x2 >= 0 && x2 < n && y2 >= 0 && y2 < m) {
//                 int new_dir = dir;
//                 if (s[x2][y2] == 'E')
//                     new_dir = (dir + 3) % 4;
//                 else if (s[x2][y2] == 'W')
//                     new_dir = (dir + 1) % 4;
//                 else if (s[x2][y2] == 'O')
//                     continue;

//                 if (dis[x2][y2][new_dir] != inf) continue;
//                 dis[x2][y2][new_dir] = dis[x][y][dir] + 1;
//                 my_queue[qcnt++] = {x2, y2, new_dir};

//             } else {
//                 // 走出去
//                 if ((x == 0 || x == n - 1) && (y == 0 || y == m - 1)) continue;
//                 if (s[x][y] == '.') {
//                     ans.push_back({x, y});
//                 }
//             }
//         }
//         return ans;
//     }
// };
class Solution {
   public:
    vector<vector<int>> ballGame(int num, vector<string>& s) {
        int n = s.size();
        int m = s[0].size();

        auto check = [&](int x, int y) {
            if (s[x][y] != '.') return false;
            int dir;
            if (x == 0) {
                dir = 1;
            } else if (x == n - 1) {
                dir = 3;
            } else if (y == 0) {
                dir = 0;
            } else {
                dir = 2;
            }
            int ct = 0;

            while (1) {
                debug(x, y);
                x += d[dir][0], y += d[dir][1];
                ct++;
                if (ct > num) return false;
                if (x >= 0 && x < n && y >= 0 && y < m) {
                    if (s[x][y] == 'E') {
                        dir = (dir + 1) % 4;
                    } else if (s[x][y] == 'W') {
                        dir = (dir + 3) % 4;
                    } else if (s[x][y] == 'O') {
                        return true;
                    }
                } else {
                    return false;
                }
            }
            return false;
        };

        vector<vector<int>> ans;
        for (int i = 1; i < m - 1; i++) {
            if (check(0, i)) {
                ans.push_back({0, i});
            }
            if (check(n - 1, i)) {
                ans.push_back({n - 1, i});
            }
        }
        for (int i = 1; i < n - 1; i++) {
            if (check(i, 0)) {
                ans.push_back({i, 0});
            }
            if (check(i, m - 1)) {
                ans.push_back({i, m - 1});
            }
        }
        return ans;
    }
};

// int main() {
// #ifdef LOCAL
//     freopen("./data.in", "r", stdin);
// #endif
//     int n = 5;
//     vector<string> s = {".....", "..E..", ".WO..", "....."};
//     // n = 4;
//     // s = {"..E.", ".EOW", "..W."};
//     Solution sol;
//     auto it = sol.ballGame(n, s);
//     debug(it);
// }