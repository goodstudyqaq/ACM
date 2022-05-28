#include <bits/stdc++.h>

#include <iostream>
#include <set>

using namespace std;

vector<long long> ans = {
    0,
    1,
    2,
    5,
    12,
    30,
    73,
    183,
    456,
    1151,
    2900,
    7361,
    18684,
    47652,
    121584,
    311259,
    797311,
    2047384,
    5260692,
    13542718,
    34884239,
    89991344,
    232282110,
    600281932,
    1552096361,
    4017128206,
};

long long solveProblem2(int N) {
    return ans[N];
}

// long long solveProblem2(int N) {
//     vector<vector<bool>> vis(N + 1, vector<bool>(N + 1));

//     vis[0][0] = 1;
//     vis[1][0] = 1;
//     long long ans = 0;
//     int d[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
//     function<void(int, int, int)> dfs = [&](int x, int y, int depth) {
//         if (depth == N) {
//             ans++;
//             return;
//         }
//         for (int i = 0; i < 4; i++) {
//             int nxt_x = x + d[i][0], nxt_y = y + d[i][1];
//             if (nxt_x >= 0 && nxt_x <= N && nxt_y >= 0 && nxt_y <= N && vis[nxt_x][nxt_y] == 0) {
//                 vis[nxt_x][nxt_y] = 1;
//                 dfs(nxt_x, nxt_y, depth + 1);
//                 vis[nxt_x][nxt_y] = 0;
//             }
//         }
//     };
//     dfs(1, 0, 1);
//     return ans;
// }

int main() {
    for (int i = 2; i <= 25; i++) {
        cout << i << ' ' << solveProblem2(i) << endl;
    }
    return 0;
}
