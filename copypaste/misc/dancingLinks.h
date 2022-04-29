#include <bits/stdc++.h>
using namespace std;
struct DLX {
   private:
    int n, m, size;
    vector<int> U, D, R, L, Row, Col;
    vector<int> H;  //行头结点
    vector<int> S;  //每一列有多少结点
    void init(int _n, int _m) {
        n = _n, m = _m;
        ansd = inf;
        for (int i = 0; i <= m; i++) {
            S[i] = 0;
            U[i] = D[i] = i;  //初始状态下,上下自己指向自己(也就知道了头结点的值为i)
            L[i] = i - 1;
            R[i] = i + 1;
        }
        R[m] = 0, L[0] = m;  //环状,下面的Link一样也是环,这样，不管从一行中的任意一个结点都可以遍历完这一行.
        size = m;            //编号,每列的头结点编号1-m，所以size从m+1开始
        for (int i = 1; i <= n; i++)
            H[i] = -1;
    }

    void exact_remove(int c)  //删除节点c(列c),并且删除所有在这一列的节点所在的行中的所有的节点。。
    {
        L[R[c]] = L[c];
        R[L[c]] = R[c];
        for (int i = D[c]; i != c; i = D[i])
            for (int j = R[i]; j != i; j = R[j]) {
                U[D[j]] = U[j];
                D[U[j]] = D[j];
                --S[Col[j]];
            }
    }

    void repeat_remove(int c)  //只删除列
    {
        for (int i = D[c]; i != c; i = D[i])
            L[R[i]] = L[i], R[L[i]] = R[i];
    }

    void exact_resume(int c)  //恢复节点c(列c),以及恢复所有在这一列的节点所在的行中的所有的节点。
    {
        for (int i = U[c]; i != c; i = U[i])
            for (int j = L[i]; j != i; j = L[j])
                ++S[Col[U[D[j]] = D[U[j]] = j]];
        L[R[c]] = R[L[c]] = c;
    }

    void repeat_resume(int c) {
        for (int i = U[c]; i != c; i = U[i])
            L[R[i]] = R[L[i]] = i;
    }

    int f()  //估价函数
    {
        vector<bool> vv(m + 1);
        int ret = 0, c, i, j;
        for (c = R[0]; c != 0; c = R[c]) vv[c] = 1;
        for (c = R[0]; c != 0; c = R[c])
            if (vv[c]) {
                ret++, vv[c] = 0;
                for (i = D[c]; i != c; i = D[i])
                    for (j = R[i]; j != i; j = R[j])
                        vv[Col[j]] = 0;
            }
        return ret;
    }

   public:
    const int inf = numeric_limits<int>::max() / 2;
    vector<int> ans;
    int ansd;
    DLX(int _n, int _m) {
        n = _n;
        m = _m;
        int maxnnode = n * m + 1;
        U.resize(maxnnode);
        D.resize(maxnnode);
        L.resize(maxnnode);
        R.resize(maxnnode);
        Row.resize(maxnnode);
        Col.resize(maxnnode);
        H.resize(n + 1);
        S.resize(m + 1);
        ans.resize(n + 1);
        init(n, m);
    }
    DLX() {}

    void link(int r, int c)  //第r行,第c列
    {
        ++S[Col[++size] = c];  //第size个结点的列为c,当前列的节点数++
        Row[size] = r;         //第size个节点行位置为r
        D[size] = D[c];
        U[D[c]] = size;
        U[size] = c;
        D[c] = size;
        if (H[r] < 0)
            H[r] = L[size] = R[size] = size;
        else {
            R[size] = R[H[r]];
            L[R[H[r]]] = size;
            L[size] = H[r];
            R[H[r]] = size;
        }
    }

    // 和普通搜索一样，这里表示搜索成功，可以得到方案，也可以得到所有方案的个数。
    // 看题目要求, 这里是只得到 1 个方案
    // 精确覆盖，每一列有且仅有 1 个 1
    bool exact_dance(int d)  //深度
    {
        if (R[0] == 0) {
            ansd = d;
            return true;
        }
        int c = R[0];
        for (int i = R[0]; i != 0; i = R[i])
            if (S[i] < S[c])
                c = i;
        exact_remove(c);  //找到节点数最少的列，当前元素不是原图上0,1的节点,而是列头结点
        for (int i = D[c]; i != c; i = D[i]) {
            ans[d] = Row[i];  //列头结点下面的一个节点
            for (int j = R[i]; j != i; j = R[j])
                exact_remove(Col[j]);
            if (exact_dance(d + 1)) return true;

            for (int j = L[i]; j != i; j = L[j])
                exact_resume(Col[j]);
        }
        exact_resume(c);
        return false;
    }
    // 重复覆盖，选最少的行，使得每一列至少有 1 个 1
    void repeat_dance(int d) {
        if (d + f() >= ansd) return;
        if (R[0] == 0) {
            if (d < ansd) ansd = d;
            // real_ans = ans; // 存方案
            return;
        }
        int c = R[0], i, j;
        for (i = R[0]; i; i = R[i])
            if (S[i] < S[c]) c = i;
        for (i = D[c]; i != c; i = D[i]) {
            ans[d] = Row[i];
            repeat_remove(i);
            for (j = R[i]; j != i; j = R[j]) repeat_remove(j);
            repeat_dance(d + 1);
            for (j = L[i]; j != i; j = L[j]) repeat_resume(j);
            repeat_resume(i);
        }
    }
};
// 下标从 1 开始