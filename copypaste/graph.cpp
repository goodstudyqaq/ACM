#include <bits/stdc++.h>
using namespace std;

namespace GraphReader {
/*
	1. 建图 建图的方式有很多，下面是几类
	*/
// vector 存图
void readGraphToVector(int n, int m) {
    // n: 点的范围 [1, n]
    // m: 边的个数
    vector< vector< int > > V;
    V.resize(n + 1);
    int u, v;
    for (int i = 1; i <= m; i++) {
        cin >> u >> v;
        V[u].push_back(v);
        // V[v].push_back(u); // 是否是双向边
    }
}

// 链式前向星
// https://oi-wiki.org//graph/save/#_14
struct GraphListReader {
    struct Edge {
        int u, v, nxt;
        // 其他信息 如权重等。。
        // extra_info
    };
    vector< Edge > edges;
    vector< int > head;
    int ecnt;

    void add_edge(int u, int v) {
        edges[ecnt] = (Edge){u, v, head[u]};
        head[u] = ecnt++;
    }

    void read(int n, int m) {
        head.resize(n + 1, -1);
        edges.resize(m);
        ecnt = 0;
        int u, v;
        for (int i = 1; i <= m; i++) {
            cin >> u >> v;
            add_edge(u, v);
        }
    }
};
}  // namespace GraphReader

namespace ShortestPath {

}