__global__ void upper_triangle_rowwise(
    const float* __restrict__ a, int n,
    const float* __restrict__ b, int m,
    float* __restrict__ out_sum)     // single-element device buffer
{
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    if (x >= n) return;

    // Every thread processes an entire row x, only taking elements where y > x
    float local = 0.0f;
    float ax = a[x];
    for (int y = x + 1; y < m; ++y) {
        local += ax * b[y];
    }

    // Atomically add the local sum to the output sum
    atomicAdd(out_sum, local);
}