#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif


struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

__global__ void upper_triangle_rowwise(
    const float* __restrict__ a, int n,
    const float* __restrict__ b, int m,
    float* __restrict__ out_sum)     // single-element device buffer
{
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    if (x >= n) return;

    // 每个线程处理一整行 x，只取 y > x 的元素
    // Every 
    float local = 0.0f;
    float ax = a[x];
    for (int y = x + 1; y < m; ++y) {
        local += ax * b[y];
    }

    atomicAdd(out_sum, local);
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    vector<int> a;
    vector<int> b;
    int n = a.size();
    int m = b.size();
    int sum = 0;
    for (int x = 0; x < n; x++) {
        for (int y = x + 1; y < m; y++) {
            sum += a[x] * b[y];
        }
    }
    

}